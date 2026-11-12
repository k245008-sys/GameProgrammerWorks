#include "EnemyState_Idle.h"
#include "EnemyBase.h"
#include "Player.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_Idle::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim("Idle");
	}
	elapsedTime += Time::GameDeltaTime();

	parent->SetVelocityXZ(VGet(0, 0, 0));

	CommonFunc_EnemyState esFunc;
	esFunc.JudgeChaseOrAttackOrAimOrWaitAndSee(this);
}

void EnemyState_Idle::End()
{
}
