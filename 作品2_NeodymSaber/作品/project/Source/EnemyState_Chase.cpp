#include "EnemyState_Chase.h"
#include "EnemyBase.h"
#include "Player.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_Chase::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim("Move");
	}

	VECTOR dist = player->GetPos() - parent->GetPos();
	MATRIX mRotY = MGetRotY(atan2f(dist.x, dist.z));
	VECTOR setVel = VGet(0, 0, ENEMY_CHASE_SPEED) * mRotY;
	parent->MoveVelocityXZ(ENEMY_CHASE_vel_VELOCITY_SPEED, setVel);
	parent->MoveRotY(ENEMY_CHASE_vel_ROT_Y_SPEED, atan2f(dist.x, dist.z));

	if (VSize(dist) <= parent->GetChaseDistLeave())
		nextStateName = "Idle";
}

void EnemyState_Chase::End()
{
}
