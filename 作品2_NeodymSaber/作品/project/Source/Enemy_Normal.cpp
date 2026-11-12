#include "Enemy_Normal.h"
#include <assert.h>

Enemy_Normal::Enemy_Normal(const VECTOR& _pos, const float& _judgeStartDistToPlayer)
	: EnemyBase(_pos, _judgeStartDistToPlayer)
{
	Init();
}

Enemy_Normal::~Enemy_Normal()
{
	EnemyBase::~EnemyBase();
}

void Enemy_Normal::Update()
{
	EnemyBase::Update();
}

void Enemy_Normal::Draw()
{
	EnemyBase::Draw();
}

void Enemy_Normal::Init()
{
	hModel = MV1LoadModel("data/model/testPlayer.mv1");
	assert(hModel > 0);

	stateManager->AddState("WaitStart", &s_waitStart);
	stateManager->AddState("Idle", &s_idle);
	stateManager->AddState("Damage", &s_damage);
	stateManager->AddState("Snap", &s_snap);
	stateManager->AddState("Chase", &s_chase);
	stateManager->AddState("WaitAndSee", &s_waitAndSee);
	stateManager->AddState("AttackClose", &s_attackClose);
	stateManager->AddState("Aim", &s_aim);
	stateManager->AddState("Fire", &s_fire);

	collRadius = ENEMY_NORMAL_COLL_RAD;
	waitAndSeeChance = ENEMY_NORMAL_WAIT_AND_SEE_CHANCE;
	defModelColor = ENEMY_NORMAL_COLOR;
	waitAndSeeBackDist = ENEMY_NORMAL_WAIT_AND_SEE_BACK_DIST;
	EnemyBase::Init();
}
