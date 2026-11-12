#include "Enemy_Bomb.h"
#include <assert.h>
#include "EnemyValue.h"
#include "EnemyState_Explosion.h"
#include "EnemyState_Idle_Bomb.h"

Enemy_Bomb::Enemy_Bomb(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot)
	: EnemyBase(_hModel, _anim, _pos, _startDist, _typeName, _rot)
{
	Init();
}

Enemy_Bomb::~Enemy_Bomb()
{
}

void Enemy_Bomb::Update()
{
	EnemyBase::Update();
}

void Enemy_Bomb::Draw()
{
	EnemyBase::Draw();
}

void Enemy_Bomb::Damage(const VECTOR& _vel, const float& _time)
{
	stateManager->ChangeCurrentState("Explosion");
}

void Enemy_Bomb::BeDead(const VECTOR& _vel)
{
	stateManager->ChangeCurrentState("Explosion");
}

void Enemy_Bomb::Snap(const VECTOR& _snapPos, const float& _finishDist)
{
	if (stateManager->GetCurrentStateName() == "Explosion")
		return;
	EnemyBase::Snap(_snapPos, _finishDist);
}

void Enemy_Bomb::Init()
{
	collRadius = ENEMY_BOMB_COLL_RAD;
	waitAndSeeChance = ENEMY_BOMB_WAIT_AND_SEE_CHANCE;
	judgeBackDistNear = ENEMY_BOMB_WAIT_AND_SEE_BACK_DIST;
	chaseDistLeave = ENEMY_BOMB_JUDGE_CHASE_DIST_LEAVE;
	modelColor = ENEMY_BOMB_COLOR;
	ambColor = ENEMY_BOMB_AMB_COLOR;
	hp = 1;
	EnemyBase::Init();
	stateManager->AddState("Idle", new EnemyState_Idle_Bomb());
	stateManager->AddState("Explosion", new EnemyState_Explosion());
}

void Enemy_Bomb::ResetWasSnap()
{
	if (stateManager->GetCurrentStateName() == "Explosion")
		return;
	if (wasSnap)
	{
		wasSnap = false;
		velocity.y = 0;
		stateManager->ChangeCurrentState("Explosion");
	}
}
