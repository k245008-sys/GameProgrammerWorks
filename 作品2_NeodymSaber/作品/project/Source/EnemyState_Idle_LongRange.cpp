#include "EnemyState_Idle_LongRange.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_Idle_LongRange::Update()
{
	EnemyState_IdleBase::Update();
	if (waiting)
		return;
	CommonFunc_EnemyState esFunc;
	esFunc.JudgeChaseOrAimOrWaitAndSee(this);
}

void EnemyState_Idle_LongRange::End()
{
}
