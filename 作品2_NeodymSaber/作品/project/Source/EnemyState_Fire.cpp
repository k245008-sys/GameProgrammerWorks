#include "EnemyState_Fire.h"
#include "ShotManager.h"
#include "EnemyBase.h"
#include "Player.h"
#include "ShotValue.h"
#include "SoundManager.h"

void EnemyState_Fire::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim("Fire");
		sound->Play("EnemyAttack_LongRange");

		VECTOR dist = player->GetPos() + VGet(0, ENEMY_AIM_ADJUST_TARGET_Y, 0) - parent->GetLaunchPortPos();
		VECTOR shotRot = VZero;
		shotRot.x= -atan2f(dist.y,
			sqrtf(dist.x * dist.x + dist.z * dist.z));
		shotRot.y = atan2f(dist.x, dist.z);
		float speed = (VSize(dist) / Time::GameDeltaTime()) / (60 * SHOT_ARRIVE_TIME);
		if (speed < SHOT_MIN_SPEED)
			speed = SHOT_MIN_SPEED;
		ShotManager* shot = FindGameObject<ShotManager>();
		shot->Fire(parent->GetLaunchPortPos(), shotRot, speed);
		parent->SetAttackCoolDown(ENEMY_ATTACK_COOL_DOWN);
	}
	elapsedTime += Time::GameDeltaTime();

	if (parent->GetIsAnimFinish())
		parent->PlayAnim("Idle");

	if (elapsedTime >= ENEMY_FIRE_TIME)
	{
		nextStateName = "Idle";
	}
}

void EnemyState_Fire::End()
{
}
