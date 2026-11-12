#include "Player.h"
#include <assert.h>
#include "PlayerValue.h"
#include "InputManager.h"
#include "Sword_Slash.h"
#include "Sword_Throw.h"
#include "ColorValue.h"
#include  "debugScreen.h"
#include "ScoreManager.h"
#include "Camera.h"
#include "CameraAdjustValue.h"
#include "PlayerState_WaitStart.h"
#include "PlayerState_Idle.h"
#include "PlayerState_Run.h"
#include "PlayerState_Attack.h"
#include "PlayerState_Attract.h"
#include "PlayerState_AttractAttack.h"
#include "PlayerState_Aim.h"
#include "PlayerState_Throw.h"
#include "PlayerState_Snap.h"
#include "PlayerState_Damage.h"
#include "PlayerState_Dead.h"
#include "PlayerState_Avoid.h"
#include "PlayerState_Clear.h"
#include "RoundShadow.h"
#include "RoundShadowManager.h"
#include "SwordValue.h"

Player::Player()
{
	input = nullptr;
	camera = nullptr;

	roundShadow = new RoundShadow(PLAYER_SHADOW_SIZE);
	RoundShadowManager* shadowManager = FindGameObject<RoundShadowManager>();
	shadowManager->Add(roundShadow);

	stateManager = new StateManager("WaitStart");
	stateManager->AddState("WaitStart", new PlayerState_WaitStart());
	stateManager->AddState("Idle", new PlayerState_Idle());
	stateManager->AddState("Run", new PlayerState_Run());
	stateManager->AddState("Attack", new PlayerState_Attack());
	stateManager->AddState("Attract", new PlayerState_Attract());
	stateManager->AddState("AttractAttack", new PlayerState_AttractAttack());
	stateManager->AddState("Aim", new PlayerState_Aim());
	stateManager->AddState("Throw", new PlayerState_Throw());
	stateManager->AddState("Snap", new PlayerState_Snap());
	stateManager->AddState("Damage", new PlayerState_Damage());
	stateManager->AddState("Dead", new PlayerState_Dead());
	stateManager->AddState("Avoid", new PlayerState_Avoid());
	stateManager->AddState("Clear", new PlayerState_Clear());

	swords.emplace_back(new Sword_Throw());
	swords.emplace_back(new Sword_Slash());

	hModel = MV1LoadModel("data/model/player.mv1");
	assert(hModel > 0);

	std::string animFile = "data/model/animation/";

	anim = new Animator();
	anim->SetModel(hModel);
	anim->LoadFile("TPose", "data/model/player.mv1");
	anim->LoadFile("Idle", animFile + "P_Wait2.mv1", PLAYER_ANIM_SETTING_IDLE);
	anim->LoadFile("Run", animFile + "P_Run.mv1", PLAYER_ANIM_SETTING_RUN);
	anim->LoadFile("Avoid", animFile + "playerAnim2_avoid.mv1", PLAYER_ANIM_SETTING_AVOID);
	anim->LoadFile("Attract1", animFile + "P_Hikiyose.mv1", PLAYER_ANIM_SETTING_ATTRACT[0]);
	anim->LoadFile("Attract2", animFile + "P_Hikiyose2.mv1", PLAYER_ANIM_SETTING_ATTRACT[1]);
	anim->LoadFile("SwingUp1", animFile + "P_Hikiyose_Up.mv1", PLAYER_ANIM_SETTING_SWING_UP[0]);
	anim->LoadFile("SwingUp2", animFile + "P_Hikiyose2_Up.mv1", PLAYER_ANIM_SETTING_SWING_UP[1]);
	anim->LoadFile("SwingDown1", animFile + "P_Hikiyose_Down.mv1", PLAYER_ANIM_SETTING_SWING_DOWN[0]);
	anim->LoadFile("SwingDown2", animFile + "P_Hikiyose2_Down.mv1", PLAYER_ANIM_SETTING_SWING_DOWN[1]);
	anim->LoadFile("Aim", animFile + "P_ThrowingPose.mv1", PLAYER_ANIM_SETTING_AIM);
	anim->LoadFile("Throw", animFile + "P_Throw.mv1", PLAYER_ANIM_SETTING_THROW);
	anim->LoadFile("Attack1", animFile + "P_Attack1.mv1", PLAYER_ANIM_SETTING_ATTACK[0]);
	anim->LoadFile("Attack2", animFile + "P_Attack2.mv1", PLAYER_ANIM_SETTING_ATTACK[1]);
	anim->LoadFile("Attack3", animFile + "P_Attack3.mv1", PLAYER_ANIM_SETTING_ATTACK[2]);
	anim->LoadFile("Damage1", animFile + "playerAnim2_damage1.mv1", PLAYER_ANIM_SETTING_DAMAGE[0]);
	anim->LoadFile("Damage2", animFile + "playerAnim2_damage2.mv1", PLAYER_ANIM_SETTING_DAMAGE[1]);
	anim->LoadFile("Dead1", animFile + "P_Dead_2.mv1", PLAYER_ANIM_SETTING_DEAD[0]);
	anim->LoadFile("Dead2", animFile + "P_Dead_3.mv1", PLAYER_ANIM_SETTING_DEAD[1]);
	anim->LoadFile("Snap", animFile + "playerAnim2_snap.mv1", PLAYER_ANIM_SETTING_SNAP);
	anim->LoadFile("Snap", animFile + "playerAnim2_snap.mv1", PLAYER_ANIM_SETTING_SNAP);
	anim->LoadFile("AirDown", animFile + "P_GoingDownPose.mv1", PLAYER_ANIM_SETTING_AIR_DOWN);
	anim->LoadFile("Grounding", animFile + "P_Grounding.mv1", PLAYER_ANIM_SETTING_GROUNDING);
	anim->LoadFile("Clear", animFile + "P_Clear.mv1", PLAYER_ANIM_SETTING_CLEAR);

	Reset();

	adjustDownCollStartPos = PLAYER_ADJUST_RAY_START_POS_JUDGE_ON_GROUND;
	downCollSizeOnGround = PLAYER_DOWN_COLL_SIZE_ON_GROUND;
	downCollSizeInAir = PLAYER_DOWN_COLL_SIZE_IN_AIR;
	adjustRayStartPosWall = PLAYER_ADJUST_RAY_START_POS_JUDGE_ON_WALL;
	wallCollSize = PLAYER_WALL_COLL_SIZE;
}

Player::~Player()
{
	swords.clear();
	delayedPos.clear();
}

void Player::Update()
{
	if (transform.position.y < -500.0f)
		transform.position = VZero;

	MV1SetMaterialDifColor(hModel, 0, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
	MV1SetMaterialAmbColor(hModel, 0, GetColorF(0.25f, 0.25f, 0.25f, 1.0f));
	anim->SetModel(hModel);

	if (enableInfiniteAttract)
		attractGaugeAmount = PLAYER_ATTRACT_GAUGE_AMOUNT_MAX;
	isInvincible = debugInvincible;

	std::string curState = stateManager->GetCurrentStateName();
	if (hp <= 0 && curState != "Dead")
		stateManager->ChangeCurrentStateOnce("Dead");

	CharaBase::Update();

	delayedTimer += Time::GameDeltaTime();
	delayedPos.emplace_back(transform.position);
	if (delayedTimer >= CAMERA_FOLLOW_PLAYER_DELAY_TIME)
	{
		for (auto it = delayedPos.begin(); it != delayedPos.end();)
		{
			if (*it == delayedPos.front())
			{
				delayedPos.erase(it);
				break;
			}
			it++;
		}
	}

#ifdef _DEBUG
	if (input->IsKeyPushDown(CAMERA_FOLLOW_PLAYER_DELAYED_POS_ENABLE_DRAW_INPUT_KEY))
		enableDelayedPos = enableDelayedPos ? false : true;
#endif

	if (input->IsTriggerPushDown("L") || input->IsTriggerPushDown("R"))
		camera->SetRestRot(CAMERA_RESET_ROT_Y_SPEED, transform.rotation.y, true);

	for (auto& sword : swords)
	{
		sword->SetParent(this);
		sword->AssignFindObjToField();
		sword->Update();
	}

	if (curState != "Attack")
	{
		if (judgeContinueAttackTime > 0)
			judgeContinueAttackTime -= Time::GameDeltaTime();
		else
			attackComboNum = 0;
		if (attackCoolDown > 0)
			attackCoolDown -= Time::GameDeltaTime();
		else if (attackComboNum >= PLAYER_ATTACK_COMBO_NUM_MAX)
			attackComboNum = 0;
	}

	if (invincibleTime > 0)
	{
		invincibleTime -= Time::GameDeltaTime();
		isInvincible = true;
	}
	if (invincibleTime < 0)
	{
		invincibleTime = 0;
		isInvincible = false;
	}

	if (avoidCoolDown > 0)
	{
		avoidCoolDown -= Time::GameDeltaTime();
		if (avoidCoolDown < 0)
			avoidCoolDown = 0;
	}
	if (attractCoolDown > 0)
		attractCoolDown -= Time::GameDeltaTime();
	if (curState != "Attract" && curState != "AttractAttack")
	{
		attractGaugeAmount += PLAYER_ATTRACT_GAUGE_RECOVERY;
		if (attractGaugeAmount > PLAYER_ATTRACT_GAUGE_AMOUNT_MAX)
			attractGaugeAmount = PLAYER_ATTRACT_GAUGE_AMOUNT_MAX;
	}

#ifdef _DEBUG
	if (input->IsKeyPushDown("7"))
	{
		transform.position = PLAYER_START_POS;
		velocity = VZero;
	}
	if (input->IsKeyPushDown("I"))
		debugInvincible = debugInvincible ? false : true;

	if (input->IsKeyPushDown("0"))
		enableInfiniteAttract = enableInfiniteAttract ? false : true;

	if (input->IsKeyPushDown("6"))
		enableDebugSpeed = enableDebugSpeed ? false : true;
	if (input->IsKeyPushDown("8"))
	{
		VECTOR dist = camera->GetPos() - transform.position;
		VECTOR distTar = camera->GetNormalTarget() - camera->GetPos();
		transform.position = VGet(7000, 200, 22500);
		camera->SetPos(transform.position + dist);
		camera->SetNormalTarget(camera->GetPos() + distTar);
	}
	if (input->IsKeyPushDown("H"))
	{
		hp++;
		if (hp > PLAYER_HP_MAX)
			hp = PLAYER_HP_MAX;
	}
	if (input->IsKeyPushDown("G"))
	{
		hp--;
		if (hp < 0)
			hp = 0;
	}
#endif
}

void Player::Draw()
{
	MATRIX mat = MGetScale(transform.scale);
	mat *= MGetRotZ(transform.rotation.z);
	mat *= MGetRotX(transform.rotation.x);
	mat *= MGetRotY(transform.rotation.y + DEGREE * 180);
	mat *= MGetTranslate(transform.position + adjustDrawPos + PLAYER_ADJUST_DRAW_POS + shakePos);
	MV1SetMatrix(hModel, mat);
	MV1DrawModel(hModel);
	for (auto& it : swords)
	{
		it->SetParent(this);
		it->Draw();
	}
	stateManager->SetParentToCurrentState(this);
	if (stateManager != nullptr)
		stateManager->Draw();

	DrawDelayedPos();

	roundShadow->Draw();
}

void Player::AssignFindObjToField()
{
	CharaBase::AssignFindObjToField();
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	camera = FindGameObject<Camera>();
}

Sword_Throw* Player::GetSword_Throw()
{
	Sword_Throw* sw_throw = nullptr;
	for (auto& it : swords)
	{
		sw_throw = dynamic_cast<Sword_Throw*>(it);
		if (sw_throw != nullptr)
			return sw_throw;
	}
	return nullptr;
}

Sword_Slash* Player::GetSword_Slash()
{
	Sword_Slash* sw_slash = nullptr;
	for (auto& it : swords)
	{
		sw_slash = dynamic_cast<Sword_Slash*>(it);
		if (sw_slash != nullptr)
			return sw_slash;
	}
	return nullptr;
}

VECTOR Player::GetLeftHandPos()
{
	return GetFrameWorldPos("QuickRigCharacter_LeftHand");
}

VECTOR Player::GetRightHandPos()
{
	return GetFrameWorldPos("QuickRigCharacter_RightHand");
}

VECTOR Player::GetLeftHandRot()
{
	return GetFrameWorldRot("QuickRigCharacter_LeftHand");
}

VECTOR Player::GetRightHandRot()
{
	return GetFrameWorldRot("QuickRigCharacter_RightHand");
}

VECTOR Player::GetHipsPos()
{
	return GetFrameWorldPos("QuickRigCharacter_Hips");
}

VECTOR Player::GetHipsRot()
{
	return GetFrameWorldRot("QuickRigCharacter_Hips");
}

bool Player::GetIsAnimFinish()
{
	return anim->IsFinish();
}

void Player::UpdateAnim()
{
	std::string curState = stateManager->GetCurrentStateName();
	enableAirDownAnim = (curState == "Idle" || curState == "Run");
	if (!isGround && enableAirDownAnim && anim->GetPlay() != "AirDown")
		anim->Play("AirDown");
	if (isGround && anim->GetPlay() == "AirDown")
		anim->Play("Grounding");

	anim->Update();
	// ƒ‚[ƒVƒ‡ƒ“‚ÌŠî€ˆÊ’u‚ð‘Ì‚Ì’†‰›‚É’²®‚·‚é
	adjustDrawPos = GetFrameLocalPos("QuickRigCharacter_Hips") * MGetRotY(transform.rotation.y);
	adjustDrawPos.y = 0;
}

void Player::PlayAnim(const std::string& _name)
{
	if (GetPlayAnim() == "AirDown" && (_name == "Run" || _name == "Idle") &&
		!isGround)
		return;
	if (anim->GetPlay() == "Grounding" &&
		!anim->IsFinish() && _name == "Idle")
		return;
	anim->Play(_name);
}

void Player::PlayDamageAnim()
{
	PlayAnimRand("Damage", PLAYER_ANIM_SETTING_DAMAGE);
}

void Player::SetAnimBlendFrame(const std::string& _name, const float& _blendFrame)
{
	anim->SetBlendFrame(_name, _blendFrame);
}

void Player::ResetAnimBlendFrame(const std::string& _name)
{
	anim->ResetBlendFrame(_name);
}

void Player::ReduceAttractGaugeAmount(const float& _reduce)
{
	attractGaugeAmount -= _reduce;
	if (attractGaugeAmount < 0)
	{
		attractGaugeAmount = 0;
		attractCoolDown = PLAYER_ATTRACT_COOL_DOWN_GAUGE_ZERO;
	}
}

void Player::Damage(const VECTOR& _damageVel)
{
	if (isInvincible ||
		stateManager->GetCurrentStateName() == "Damage" ||
		stateManager->GetCurrentStateName() == "Dead")
		return;

	camera->SetShakeCamera(CAMERA_PLAYER_DAMAGE_SHAKE_RANGE_MAX, CAMERA_PLAYER_DAMAGE_SHAKE_SPEED, CAMERA_PLAYER_DAMAGE_SHAKE_TIME);
	hp--;
	if (hp <= 0)
	{
		hp = 0;
		ChangeStateOnce("Dead");
		return;
	}
	ChangeStateOnce("Damage");
	SetVelocityXZ(_damageVel);
}

void Player::DrawDelayedPos()
{
	if (!enableDelayedPos)
		return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_ALPHA);
	DrawSphere3D(delayedPos.front(), CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_RAD,
		CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_DIV_NUM, CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_DIF_COLOR,
		CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_SPC_COLOR, (int)CAMERA_FOLLOW_PLAYER_DELAYED_POS_DRAW_FILL);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Player::SwordSlashCapsuleColl(const VECTOR& _start, const VECTOR& _end, const float& _rad)
{
	Sword_Slash* sw_slash = GetSword_Slash();
	return (bool)HitCheck_Capsule_Capsule(sw_slash->GetCollRootPos(), sw_slash->GetCollTipPos(), SWORD_SLASH_COLL_RAD, _start, _end, _rad);
}

void Player::Reset()
{
	delayedPos.clear();
	stateManager->ChangeCurrentStateOnce("WaitStart");
	anim->SetBlendFrame("Idle", 1);
	anim->Play("Idle");

	transform.position = PLAYER_START_POS;
	transform.rotation = VZero;
	float s = PLAYER_DEFAULT_SCALE;
	transform.scale = VGet(s, s, s);

	hp = PLAYER_HP_MAX;
	attackComboNum = 0;
	judgeContinueAttackTime = 0;
	attackCoolDown = 0;
	isInvincible = false;
	avoidCoolDown = 0;
	isSnap = false;
	attractGaugeAmount = PLAYER_ATTRACT_GAUGE_AMOUNT_MAX;
	enableInfiniteAttract = false;
	enableDebugSpeed = false;
	delayedTimer = 0;
	enableDelayedPos = false;
	invincibleTime = 0;
	debugInvincible = false;
	enableAirDownAnim = false;
}