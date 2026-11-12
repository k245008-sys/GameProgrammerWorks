#include "EnemyState_IdleBase.h"
#include "EnemyBase.h"
#include "Player.h"
#include <string>

void EnemyState_IdleBase::Update()
{
	if (parent->GetCurrentAnim() != "Idle" && !parent->GetIsAnimFinish())
	{
		if (parent->GetCurrentAnim().substr(0, 4) != "Snap")
			return;
	}

	if (elapsedTime == 0)
	{
		parent->PlayAnim("Idle");
	}
	elapsedTime += Time::GameDeltaTime();

	VECTOR reduce = parent->GetReduceKnockBackSpeed();
	if (VSize(reduce) == 0)
		parent->SetVelocityXZ(VZero);
	else
		parent->MoveVelocityXZ(reduce.z, VZero);

	if (parent->GetAnimBlendFrame("Idle") != parent->GetAnimDefBlendFrame("Idle"))
	{
		if (parent->GetIsAnimFinish())
		{
			parent->ResetAnimBlendFrame("Idle");
			waiting = false;
		}
		else
		{
			parent->SetVelocityXZ(VZero);
			waiting = true;
		}
	}
	else
		waiting = false;
}

void EnemyState_IdleBase::End()
{
	parent->SetReduceKnockBackSpeed(VZero);
	waiting = false;
}
