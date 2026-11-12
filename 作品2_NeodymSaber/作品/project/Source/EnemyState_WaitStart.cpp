#include "EnemyState_WaitStart.h"
#include "EnemyBase.h"
#include "Player.h"

void EnemyState_WaitStart::Update()
{
	if(elapsedTime == 0)
	parent->PlayAnim("Idle");
	elapsedTime += Time::GameDeltaTime();
	parent->SetVelocityXZ(VZero);
	if (VSize(parent->GetPos() - player->GetPos()) <= parent->GetJudgeStartDistToPlayer() ||
		parent->GetJudgeStartDistToPlayer() <= 0)
	{
		nextStateName = "Idle";
	}
}

void EnemyState_WaitStart::End()
{
}
