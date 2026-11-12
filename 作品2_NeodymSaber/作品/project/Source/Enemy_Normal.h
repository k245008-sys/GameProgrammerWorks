#pragma once
#include "EnemyBase.h"
#include "EnemyState_WaitStart.h"
#include "EnemyState_IdleBase.h"
#include "EnemyState_Damage.h"
#include "EnemyState_Snap.h"
#include "EnemyState_Chase.h"
#include "EnemyState_WaitAndSee.h"
#include "EnemyState_AttackClose.h"
#include "EnemyState_Aim.h"
#include "EnemyState_Fire.h"

/*
	í èÌÇÃìGÉNÉâÉX
	àªïî
*/

class Enemy_Normal : public EnemyBase
{
public:
	Enemy_Normal(const VECTOR& _pos, const float& _judgeStartDistToPlayer);
	~Enemy_Normal();
	void Update()override;
	void Draw()override;

private:
	void Init()override;

	EnemyState_WaitStart s_waitStart;
	EnemyState_IdleBase s_idle;
	EnemyState_Damage s_damage;
	EnemyState_Snap s_snap;
	EnemyState_Chase s_chase;
	EnemyState_WaitAndSee s_waitAndSee;
	EnemyState_AttackClose s_attackClose;
	EnemyState_Aim s_aim;
	EnemyState_Fire s_fire;
};