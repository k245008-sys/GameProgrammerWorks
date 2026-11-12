#include "EnemyState_Idle_CloseRange.h"
#include "CommonFunc_EnemyState.h"
#include "EnemyBase.h"

void EnemyState_Idle_CloseRange::Update()
{
	EnemyState_IdleBase::Update();
	if (waiting)
		return;
	CommonFunc_EnemyState esFunc;
	esFunc.JudgeChaseOrAttackCloseOrWaitAndSee(this);
}

void EnemyState_Idle_CloseRange::End()
{
}
