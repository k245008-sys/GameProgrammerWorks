#include "EnemyState_Idle_Bomb.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_Idle_Bomb::Update()
{
	EnemyState_IdleBase::Update();
	if (waiting)
		return;
	CommonFunc_EnemyState esFunc;
	esFunc.JudgeChaseOrWaitAndSee(this);
}

void EnemyState_Idle_Bomb::End()
{
}
