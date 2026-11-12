#include "Enemy_LongRange.h"
#include <assert.h>
#include "EnemyState_Aim.h"
#include "EnemyState_Fire.h"
#include "EnemyState_Damage.h"
#include "EnemyState_Dead.h"
#include "EnemyState_Idle_LongRange.h"

Enemy_LongRange::Enemy_LongRange(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot)
	: EnemyBase(_hModel, _anim, _pos, _startDist, _typeName, _rot)
{
	Init();
}

Enemy_LongRange::~Enemy_LongRange()
{
}

void Enemy_LongRange::Update()
{
	EnemyBase::Update();
}

void Enemy_LongRange::Draw()
{
	EnemyBase::Draw();
}

void Enemy_LongRange::Init()
{
	collRadius = ENEMY_LONG_RANGE_COLL_RAD;
	waitAndSeeChance = ENEMY_LONG_RANGE_WAIT_AND_SEE_CHANCE;
	judgeBackDistNear = ENEMY_LONG_RANGE_WAIT_AND_SEE_BACK_DIST;
	chaseDistLeave = ENEMY_LONG_RANGE_JUDGE_CHASE_DIST_LEAVE;
	modelColor = ENEMY_LONG_RANGE_COLOR;
	ambColor = ENEMY_LONG_RANGE_AMB_COLOR;
	EnemyBase::Init();

	stateManager->AddState("Idle", new EnemyState_Idle_LongRange());
	stateManager->AddState("Aim", new EnemyState_Aim());
	stateManager->AddState("Fire", new EnemyState_Fire());
	stateManager->AddState("Damage", new EnemyState_Damage());
	stateManager->AddState("Dead", new EnemyState_Dead());
}
