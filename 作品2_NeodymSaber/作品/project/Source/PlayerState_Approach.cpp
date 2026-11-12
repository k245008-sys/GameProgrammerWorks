#include "PlayerState_Approach.h"
#include "../Library/Time.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayerValue.h"

void PlayerState_Approach::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim((int)PlayerAnim::T_POSE);
	}
	elapsedTime += Time::GameDeltaTime();

	// –Ú•W‚Ì“G‚Öi‚İ‘±‚¯‚é
	VECTOR enePos = parent->GetTargetEnemy()->GetPos();
	VECTOR dist = enePos - parent->GetPos();
	VECTOR dir = VNorm(dist);
	parent->SetVelocityXZ(dir * PLAYER_APPROACH_SPEED);
	parent->SetRotY(atan2f(dir.x, dir.z));

	VECTOR playerMovePos = parent->GetPos()
		+ parent->GetVelocity() * Time::GameDeltaTime();
	// ˆê’è‚Ì‹——£‚Ü‚Å—ˆ‚½‚çUŒ‚‚Ö
	if (VSize(enePos - playerMovePos) <= PLAYER_APPROACH_JUDGE_FINISH_DIST)
	{
		VECTOR eneToFinishDistPos = enePos + VNorm(dist * -1)
			* PLAYER_APPROACH_JUDGE_FINISH_DIST;
		VECTOR setVel = dist + eneToFinishDistPos;
		parent->SetVelocityXZ(setVel);
		nextStateID = (int)PlayerState::ATTACK;
	}
}

void PlayerState_Approach::End()
{
}
