#include "Enemy_CloseRange.h"
#include <assert.h>
#include "EnemyState_AttackClose.h"
#include "EnemyState_Damage.h"
#include "EnemyState_Dead.h"
#include "EnemyState_Idle_CloseRange.h"

Enemy_CloseRange::Enemy_CloseRange(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot)
	: EnemyBase(_hModel, _anim, _pos, _startDist, _typeName, _rot)
{
	Init();
}

Enemy_CloseRange::~Enemy_CloseRange()
{
}

void Enemy_CloseRange::Update()
{
	EnemyBase::Update();
}

void Enemy_CloseRange::Draw()
{
	EnemyBase::Draw();
}

void Enemy_CloseRange::Init()
{
	collRadius = ENEMY_CLOSE_RANGE_COLL_RAD;
	waitAndSeeChance = ENEMY_CLOSE_RANGE_WAIT_AND_SEE_CHANCE;
	judgeBackDistNear = ENEMY_CLOSE_RANGE_WAIT_AND_SEE_BACK_DIST;
	chaseDistLeave = ENEMY_CLOSE_RANGE_JUDGE_CHASE_DIST_LEAVE;
	modelColor = ENEMY_CLOSE_RANGE_COLOR;
	ambColor = ENEMY_CLOSE_RANGE_AMB_COLOR;
	EnemyBase::Init();

	stateManager->AddState("Idle", new EnemyState_Idle_CloseRange());
	stateManager->AddState("Damage", new EnemyState_Damage());
	stateManager->AddState("Dead", new EnemyState_Dead());
	stateManager->AddState("AttackClose", new EnemyState_AttackClose());
}
