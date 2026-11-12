#include "EnemyState_Idle_Normal.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_Idle_Normal::Update()
{
	EnemyState_IdleBase::Update();
	CommonFunc_EnemyState esFunc;
	esFunc.JudgeChaseOrAttackCloseOrAimOrWaitAndSee(this);
}

void EnemyState_Idle_Normal::End()
{
}
