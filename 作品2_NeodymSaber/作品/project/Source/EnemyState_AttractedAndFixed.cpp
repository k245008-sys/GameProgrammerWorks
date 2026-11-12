#include "EnemyState_AttractedAndFixed.h"
#include "Player.h"
#include "EnemyBase.h"

void EnemyState_AttractedAndFixed::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim("LiftedUp");
	}
	float prevTime = elapsedTime;
	elapsedTime += Time::GameDeltaTime();
	float timing = ENEMY_ATTRACTED_AND_FIXED_DROPPED_ANIM_TIMING;
	if (prevTime < timing && elapsedTime >= timing)
		parent->PlayAnim("Dropped");

	if (player->GetCurrentStateName() != "AttractAttack")
		parent->ChangeStateOnce("Idle");
}

void EnemyState_AttractedAndFixed::End()
{
	if (parent == nullptr)
		return;
	parent->SetVelocityY(0);
}
