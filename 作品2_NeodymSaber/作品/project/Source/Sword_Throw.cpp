#include "Sword_Throw.h"
#include <assert.h>
#include "SwordValue.h"
#include "Player.h"
#include "ColorValue.h"
#include "Camera.h"
#include "debugScreen.h"
#include "InputManager.h"
#include "CommonFunc_SwordState.h"
#include "PlayerValue.h"
#include "EnemyManager.h"
#include "Util.h"

Sword_Throw::Sword_Throw()
{
	stateManager = new StateManager("Equipped");
	stateManager->AddState("Equipped", &s_equipped);
	stateManager->AddState("Held", &s_held);
	stateManager->AddState("Thrown", &s_thrown);
	stateManager->AddState("Pierced", &s_pierced);
	stateManager->AddState("ComeBack", &s_comeBack);

	hModel = MV1LoadModel("data/model/sword_red.mv1");
	assert(hModel > 0);

	transform.scale = SWORD_THROW_SCALE;
	input = nullptr;
	camera = nullptr;
	player = nullptr;
	targetEnemy = nullptr;
	targetPos = VZero;
	attractGaugeAmount = SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX;
	rootFrameName = SWORD_THROW_ROOT_NAME;
	defRootPos = VZero;
}

Sword_Throw::~Sword_Throw()
{
	SwordBase::~SwordBase();
}

void Sword_Throw::Update()
{
	SwordBase::Update();
	if (stateManager->GetCurrentStateName() != "Pierced")
	{
		attractGaugeAmount += SWORD_THROW_ATTRACT_GAUGE_RECOVERY;
		if (attractGaugeAmount > SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX)
			attractGaugeAmount = SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX;
	}
}

void Sword_Throw::Draw()
{
	if (stateManager->GetCurrentStateName() == "Held")
	{
		transform.position = parent->GetRightHandPos() + SWORD_THROW_ADJUST_HELD_POS * MGetRotZXY(parent->GetRightHandRot());
		transform.rotation = parent->GetRightHandRot();
		SetFrameLocalRot(rootFrameName.c_str(), SWORD_THROW_LOCAL_HELD_ROT);
	}
	else
		SetFrameLocalRot(rootFrameName.c_str(), VZero);
	if (stateManager->GetCurrentStateName() == "Equipped")
	{
		transform.position = parent->GetHipsPos() + SWORD_THROW_ADJUST_EQUIPPED_POS
			* MGetRotZXY(parent->GetHipsRot() + SWORD_THROW_ADJUST_EQUIPPED_ROT_FOR_POS);
		transform.rotation = parent->GetHipsRot() + SWORD_THROW_ADJUST_EQUIPPED_ROT;
	}
	SwordBase::Draw();
}

void Sword_Throw::AssignFindObjToField()
{
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	camera = FindGameObject<Camera>();
	player = FindGameObject<Player>();
}

void Sword_Throw::ReduceAttractGaugeAmount(const float& _reduce)
{
	attractGaugeAmount -= _reduce;
	if (attractGaugeAmount < 0)
		attractGaugeAmount = 0;
}

void Sword_Throw::CalcTargetPos()
{
	SetTargetEnemy();
	if (targetEnemy != nullptr)
	{
		targetPos = targetEnemy->GetPos();
		return;
	}
	if (player->GetCurrentStateName() == "Attack")
	{
		float stickAngle = input->GetStickAngle("L") + camera->GetRot().y;
		targetPos = transform.position +
			VGet(0, 0, SWORD_THROW_ATTACK_THROW_JUDGE_FALL_DIST) * MGetRotY(stickAngle);
	}
	else
	{
		CommonFunc_SwordState swFunc;
		VECTOR dist = swFunc.GetDistToThrowTarget(transform.position);
		targetPos = transform.position + dist;
	}
}

void Sword_Throw::BeThrown(const bool& _isAttack)
{
	if (GetCurrentStateName() != "Equipped" &&
		GetCurrentStateName() != "Held")
		return;

	stateManager->ChangeCurrentState("Thrown");
	if (_isAttack)
	{
		CalcTargetPos();
		transform.rotation.x = SWORD_THROW_ADJUST_ROT_X_THROWN;
		VECTOR dist = targetPos - transform.position;
		transform.rotation.y = atan2f(dist.x, dist.z);
		velocity = VGet(0, 0, SWORD_THROW_SPEED) * MGetRotY(transform.rotation.y);
	}
	else
	{
		CommonFunc_SwordState swFunc;
		VECTOR dist = swFunc.GetDistToThrowTarget(transform.position);
		targetPos = transform.position + dist;
		velocity = swFunc.GetThrowVelocity(transform.position);
		transform.rotation.x = -atan2f(dist.y, sqrtf(dist.x * dist.x + dist.z * dist.z));
		transform.rotation.y = atan2f(dist.x, dist.z);
		transform.rotation.y -= DEGREE * 90;
		targetEnemy = nullptr;
	}
}

void Sword_Throw::SetTargetEnemy()
{
	if (player->GetCurrentStateName() != "Attack")
	{
		targetEnemy = nullptr;
		return;
	}
	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	bool isFirst = false;
	float minDist = 0;
	EnemyBase* nearEnemy = nullptr;
	for (auto& enemy : enemyManager->GetEnemies())
	{
		VECTOR dist = enemy->GetPos() - player->GetPos();
		if (VSize(dist) < PLAYER_ATTACK_THROW_ENABLE_ASSIST_DIST_LEAVE ||
			VSize(dist) > PLAYER_ATTACK_THROW_ENABLE_ASSIST_DIST_CLOSE)
			continue;

		using namespace Util;
		float stickAngle = input->GetStickAngle("L") + camera->GetRot().y;
		NormalizeAngle(stickAngle);
		float diffRotY = atan2f(dist.x, dist.z) - stickAngle;
		NormalizeAngle(diffRotY);
		diffRotY = fabsf(diffRotY);
		if (diffRotY > PLAYER_ATTACK_THROW_ENABLE_ASSIST_ROT_Y)
			continue;

		if (!isFirst)
		{
			isFirst = true;
			minDist = VSize(dist);
			nearEnemy = enemy;
			continue;
		}
		if (minDist > VSize(dist))
		{
			minDist = VSize(dist);
			nearEnemy = enemy;
		}
	}
	targetEnemy = nearEnemy;
}
