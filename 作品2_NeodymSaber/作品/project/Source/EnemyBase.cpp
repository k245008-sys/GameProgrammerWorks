#include "EnemyBase.h"
#include "StageManager.h"
#include "EffectManager.h"
#include "EffectValue.h"
#include "PlayerValue.h"
#include <assert.h>
#include "EnemyManager.h"
#include "ScoreManager.h"
#include "EnemyStateBase.h"
#include "EnemyState_WaitStart.h"
#include "EnemyState_WaitAndSee.h"
#include "EnemyState_Chase.h"
#include "EnemyState_AttractedAndFixed.h"
#include "EnemyState_Snap.h"
#include "RoundShadow.h"
#include "RoundShadowManager.h"
#include "Emitter.h"
#include "CommonFunc_CollDraw.h"
#include "Util.h"

EnemyBase::EnemyBase(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot)
{
	roundShadow = new RoundShadow(ENEMY_SHADOW_SIZE);
	RoundShadowManager* shadowManager = FindGameObject<RoundShadowManager>();
	shadowManager->Add(roundShadow);

	hModel = MV1DuplicateModel(_hModel);
	anim = _anim;
	anim->SetModel(hModel);
	BaseInit(_pos);
	typeName = _typeName;
	startDistToPlayer = _startDist;
	float s = ENEMY_SCALE;
	transform.scale = VGet(s, s, s);
	transform.rotation = _rot;

	chaseDistLeave = 0;
	collRadius = 0;
	adjustDownCollStartPos = ENEMY_ADJUST_RAY_START_POS_JUDGE_ON_GROUND;
	adjustDownCollStartPos = ENEMY_ADJUST_RAY_START_POS_JUDGE_ON_GROUND;
	downCollSizeOnGround = ENEMY_DOWN_COLL_SIZE_ON_GROUND;
	downCollSizeInAir = ENEMY_DOWN_COLL_SIZE_IN_AIR;
	adjustRayStartPosWall = ENEMY_ADJUST_RAY_START_POS_JUDGE_ON_WALL;
	wallCollSize = ENEMY_WALL_COLL_SIZE;
	judgeBackDistNear = 0;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	if (transform.position.y <= ENEMY_DELETE_Y)
		isDestroy = true;
	EnemyStateBase* state = dynamic_cast<EnemyStateBase*>(stateManager->GetCurrentState());
	if (state != nullptr)
		state->SetFind(player, sound);
	CharaBase::Update();
	if (doDelayDamage)
	{
		doDelayDamage = false;
		Damage(delayedDamageVel, delayedDamageTime);
	}
	isAttract = false;

	if (hp <= 0)
	{
		MV1SetMaterialDifColor(hModel, 0, ENEMY_DEAD_COLOR);
		MV1SetMaterialAmbColor(hModel, 0, ENEMY_DEAD_COLOR);
	}
	else if (inPlayerAimArea)
	{
		MV1SetMaterialDifColor(hModel, 0, ENEMY_IN_ATTRACT_RANGE_COLOR);
		MV1SetMaterialAmbColor(hModel, 0, ENEMY_IN_ATTRACT_RANGE_COLOR);
	}
	else
	{
		MV1SetMaterialDifColor(hModel, 0, modelColor);
		MV1SetMaterialAmbColor(hModel, 0, ambColor);
	}

	if (afterDamageTime > 0)
		afterDamageTime -= Time::GameDeltaTime();
	if (afterSnapTime > 0)
		afterSnapTime -= Time::GameDeltaTime();
	if (attackCoolDown > 0)
		attackCoolDown -= Time::GameDeltaTime();

	circle.SetPos(transform.position);
	circle.SetScale(startDistToPlayer / 100);
}

void EnemyBase::Draw()
{
	MATRIX mat = MGetScale(transform.scale);
	mat *= MGetRotZ(transform.rotation.z);
	mat *= MGetRotX(transform.rotation.x);
	mat *= MGetRotY(transform.rotation.y + DEGREE * 180);
	mat *= MGetTranslate(transform.position + adjustDrawPos + shakePos);
	MV1SetMatrix(hModel, mat);
	MV1DrawModel(hModel);
	stateManager->SetParentToCurrentState(this);
	if (stateManager != nullptr)
		stateManager->Draw();

	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	if (enemyManager->GetDoDisplayStartDist() &&
		stateManager->GetCurrentStateName() == "WaitStart")
		circle.Draw();

	roundShadow->Draw();
}

void EnemyBase::DrawDamageColl()
{
	CommonFunc_CollDraw cDraw;
	cDraw.DrawCapsule(GetDamageCollRoot(), GetDamageCollTip(), ENEMY_COLL_RAD, ENEMY_DRAW_COLL_COLOR, ENEMY_DRAW_COLL_ALPHA_PERCENT);
}

void EnemyBase::AssignFindObjToField()
{
	CharaBase::AssignFindObjToField();
}

void EnemyBase::UpdateAnim()
{
	anim->Update();
	// ƒ‚[ƒVƒ‡ƒ“‚ÌŠî€ˆÊ’u‚ð‘Ì‚Ì’†‰›‚É’²®‚·‚é
	adjustDrawPos = GetFrameLocalPos("Hip") * MGetRotY(transform.rotation.y);
	adjustDrawPos.y = 0;
}

void EnemyBase::Damage(const VECTOR& _vel, const float& _time)
{
	if (!isInvincible)
		hp--;
	ScoreManager* score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	score->AddOneCurrentCombo();
	if (hp <= 0)
	{
		EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
		effect->Create("Hit", transform.position + EFFECT_HIT_ADJUST_POS,
			VZero, EFFECT_HIT_DEAD_SCALE);
		ExplosionParts();
		isDestroy = true;
		return;
	}
	velocity = _vel;
	damageTime = _time;
	afterDamageTime = ENEMY_AFTER_DAMAGE_TIME;
	stateManager->ChangeCurrentState("Damage");
}

void EnemyBase::DamageOneFrameLater(const VECTOR& _vel, const float& _time)
{
	doDelayDamage = true;
	delayedDamageVel = _vel;
	delayedDamageTime = _time;
}

void EnemyBase::BeDead(const VECTOR& _vel)
{
	ScoreManager* score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	score->AddOneCurrentCombo();

	hp = 0;
	velocity = _vel;
	stateManager->ChangeCurrentState("Dead");
}

void EnemyBase::Snap(const VECTOR& _snapPos, const float& _finishDist)
{
	if (stateManager->GetCurrentStateName() == "Dead" ||
		stateManager->GetCurrentStateName() == "AttractedAndFixed")
		return;
	isAttract = true;
	ChangeStateOnce("Snap");
	snapPos = _snapPos;
	snapFinishDist = _finishDist;
}

bool EnemyBase::IsFrontStageColl()
{
	for (auto& stage : stageManager->GetAllObjects())
	{
		MV1RefreshCollInfo(stage->GetModel());
		VECTOR startPos = transform.position
			+ ENEMY_FRONT_AND_BACK_STAGE_ADJUST_RAY_START_POS;
		MV1_COLL_RESULT_POLY collResult =
			MV1CollCheck_Line(stage->GetModel(), -1,
				startPos, startPos +
				VGet(0, 0, ENEMY_FRONT_STAGE_COLL_SIZE) * MGetRotY(transform.rotation.y));
		if (collResult.HitFlag == TRUE)
			return true;
	}
	return false;
}

bool EnemyBase::IsBackStageColl()
{
	for (auto& stage : stageManager->GetAllObjects())
	{
		MV1RefreshCollInfo(stage->GetModel());
		VECTOR startPos = transform.position
			+ ENEMY_FRONT_AND_BACK_STAGE_ADJUST_RAY_START_POS;
		MV1_COLL_RESULT_POLY collResult =
			MV1CollCheck_Line(stage->GetModel(), -1,
				startPos, startPos +
				VGet(0, 0, -ENEMY_BACK_STAGE_COLL_SIZE) * MGetRotY(transform.rotation.y));
		if (collResult.HitFlag == TRUE)
			return true;
	}
	return false;
}

void EnemyBase::Init()
{
	stateManager = new StateManager("WaitStart");
	stateManager->AddState("WaitStart", new EnemyState_WaitStart());
	stateManager->AddState("WaitAndSee", new EnemyState_WaitAndSee());
	stateManager->AddState("Chase", new EnemyState_Chase());
	stateManager->AddState("AttractedAndFixed", new EnemyState_AttractedAndFixed());
	stateManager->AddState("Snap", new EnemyState_Snap());
}

void EnemyBase::BaseInit(const VECTOR& _pos)
{
	hp = ENEMY_DEFAULT_HP;
	isDestroy = false;
	transform.position = _pos;
	spawnPos = _pos;
	damageTime = 0;
	snapPos = VZero;
	snapFinishDist = 0;
	waitAndSeeTime = 0;
	afterDamageTime = 0;
	afterSnapTime = 0;
	attackCoolDown = 0;
	isAttract = false;
	isInvincible = false;
	beforeSwingPos = VZero;
	doDelayDamage = false;
	delayedDamageVel = VZero;
	delayedDamageTime = 0;
	reduceKnockBackSpeed = VZero;
	inPlayerAimArea = false;
}

void EnemyBase::ExplosionPartsOne(Emitter* _emitter, const std::string& _type)
{
	using namespace Util;

	float lifeTime = ENEMY_EXPLOSION_PARTS_LIFE_TIME;
	float fadeOut = ENEMY_EXPLOSION_PARTS_FADE_OUT_TIME;
	VECTOR vel = GetRandV(ENEMY_EXPLOSION_PARTS_VELOCITY_MIN, ENEMY_EXPLOSION_PARTS_VELOCITY_MAX);
	VECTOR reduce = ENEMY_EXPLOSION_PARTS_REDUCE_VELOCITY;
	VECTOR rotSpd = GetRandV(ENEMY_EXPLOSION_PARTS_ROT_SPEED_MIN, ENEMY_EXPLOSION_PARTS_ROT_SPEED_MAX);
	SetSignRandV(vel);
	SetSignRandV(rotSpd);
	_emitter->Create(_type, transform.position + ENEMY_EXPLOSION_PARTS_ADJUST_POS, lifeTime, fadeOut, vel, reduce, rotSpd);
}

void EnemyBase::ExplosionParts()
{
	Emitter* emitter = FindGameObject<Emitter>();
	ExplosionPartsOne(emitter, "Arm");
	ExplosionPartsOne(emitter, "Body");
	ExplosionPartsOne(emitter, "Clavicle");
	ExplosionPartsOne(emitter, "Foot");
	ExplosionPartsOne(emitter, "Hand");
	ExplosionPartsOne(emitter, "Head");
	ExplosionPartsOne(emitter, "Joint1");
	ExplosionPartsOne(emitter, "Joint2");
	ExplosionPartsOne(emitter, "Joint3");
	ExplosionPartsOne(emitter, "Leg");
	ExplosionPartsOne(emitter, "LegGuard");
	ExplosionPartsOne(emitter, "LegJoint");
	ExplosionPartsOne(emitter, "Shoulder");
	ExplosionPartsOne(emitter, "UpLeg");
	ExplosionPartsOne(emitter, "Waist1");
	ExplosionPartsOne(emitter, "Waist2");
}
