#include "EnemyState_WaitAndSee.h"
#include "EnemyBase.h"
#include "Player.h"
#include "CommonFunc_EnemyState.h"

void EnemyState_WaitAndSee::Update()
{
	distToPlayer = player->GetPos() - parent->GetPos();
	parent->MoveRotY(ENEMY_WAIT_AND_SEE_vel_ROT_Y_SPEED, atan2f(distToPlayer.x, distToPlayer.z));

	CommonFunc_EnemyState esFunc;
	if (esFunc.JudgeAttack(this))
		return;
	if (esFunc.JudgeChase(this))
		return;

	elapsedTime += Time::GameDeltaTime();
	if (elapsedTime >= parent->GetWaitAndSeeTime())
	{
		nextStateName = "Idle";
		return;
	}

	changeDirTime -= Time::GameDeltaTime();
	if (changeDirTime <= 0)
	{
		changeDirTime = ENEMY_WAIT_AND_SEE_CHANGE_vel_DIR_INTERVAL;
		if (JudgeChangeDirection())
		{
			SetVelocity();
			PlayAnim();
			return;
		}
		SetDirectionByChance();
		PlayAnim();
	}
	SetVelocity();
}

void EnemyState_WaitAndSee::End()
{
	changeDirTime = 0;
}

void EnemyState_WaitAndSee::SetDirectionToBesideOrStay()
{
	int rand = GetRand(2);
	switch (rand)
	{
	case 0:
		direction = RIGHT;
		break;
	case 1:
		direction = LEFT;
		break;
	case 2:
		direction = STAY;
		break;
	}
}

void EnemyState_WaitAndSee::SetDirectionByChance()
{
	chancePercent = GetRand(100 - 1) + 1;
	WaitAndSeePattern chance = parent->GetWaitAndSeeChance();
	if (chancePercent <= chance.beside)
		SetDirectionToBesideOrStay();
	else if (chancePercent <= chance.beside + chance.front)
		direction = FRONT;
	else if (chancePercent <= chance.beside + chance.front + chance.back)
		direction = BACK;
	else
		direction = STAY;
}

void EnemyState_WaitAndSee::SetVelocity()
{
	if (direction >= STAY)
	{
		parent->SetVelocityXZ(VZero);
		return;
	}
	float speed = 0;
	float moveRotY = 0;
	switch (direction)
	{
	case RIGHT:
		speed = ENEMY_WAIT_AND_SEE_vel_SPEED.beside;
		moveRotY = DEGREE * 90;
		break;
	case LEFT:
		speed = ENEMY_WAIT_AND_SEE_vel_SPEED.beside;
		moveRotY = DEGREE * -90;
		break;
	case FRONT:
		speed = ENEMY_WAIT_AND_SEE_vel_SPEED.front;
		break;
	case BACK:
		speed = ENEMY_WAIT_AND_SEE_vel_SPEED.back;
		moveRotY = DEGREE * 180;
		break;
	default:
		break;
	}
	VECTOR dist = player->GetPos() - parent->GetPos();
	float diffRotY = atan2f(dist.x, dist.z);
	moveRotY += diffRotY;
	parent->SetVelocityXZ(VGet(0, 0, speed)
		* MGetRotY(moveRotY));
}

bool EnemyState_WaitAndSee::JudgeChangeDirection()
{
	if (parent->IsFrontStageColl() || parent->IsBackStageColl())
	{
		SetDirectionToBesideOrStay();
		return true;
	}
	if (VSize(distToPlayer) <= parent->GetJudgeBackDistNear())
	{
		direction = BACK;
		return true;
	}
	return false;
}

void EnemyState_WaitAndSee::PlayAnim()
{
	if (direction == STAY)
		parent->PlayAnim("Idle");
	else
		parent->PlayAnim("Move");
}
