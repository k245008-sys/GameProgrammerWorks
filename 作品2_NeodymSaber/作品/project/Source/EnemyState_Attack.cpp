#include "EnemyState_Attack.h"
#include "Player.h"
#include "EnemyValue.h"
#include "EnemyBase.h"
#include "CommonFunc_EnemyState.h"
#include "SoundManager.h"
#include "SoundValue.h"

void EnemyState_Attack::Update()
{
	VECTOR dist = player->GetPos() - parent->GetPos();
	if (elapsedTime == 0)
	{
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->PlaySE(sound->ENEMY_ATTACK_WARNING, SOUND_VOLUME_ENEMY_ATTACK_WARNING);
		parent->PlayAnim("TPose");
		firstDist = dist;
	}
	elapsedTime += Time::GameDeltaTime();

	parent->SetRotY(atan2f(firstDist.x, firstDist.z));
	if (elapsedTime < ENEMY_BEFORE_ATTACK_TIME)
	{
		blinkingTimer += Time::GameDeltaTime();
		if (blinkingTimer < ENEMY_BEFORE_ATTACK_BLINKING_TIME)
			parent->SetModelColor(ENEMY_ATTACK_WARNING_COLOR);
		else if (blinkingTimer < ENEMY_BEFORE_ATTACK_BLINKING_TIME * 2)
			parent->ResetModelColor();
		else
			blinkingTimer = 0;

		parent->SetVelocityXZ(VGet(0,0,0));
	}
	else if (elapsedTime < ENEMY_BEFORE_ATTACK_TIME +
		ENEMY_ATTACK_FORWARD_TIME)
	{
		parent->SetModelColor(ENEMY_ATTACK_WARNING_COLOR);
		parent->SetVelocityXZ(VNorm(firstDist) * ENEMY_ATTACK_FORWARD_SPEED);
	}
	else
	{
		CommonFunc_EnemyState esFunc;
		esFunc.JudgeChaseOrAttackOrAimOrWaitAndSee(this);
		return;
	}

	if (elapsedTime >= ENEMY_ATTACK_COLL_TIMING_START && 
		elapsedTime < ENEMY_ATTACK_COLL_TIMING_END)
	{
		PlayerCollision();
	}
}

void EnemyState_Attack::End()
{
	parent->ResetModelColor();
	parent->SetAttackCoolDownLeft(ENEMY_ATTACK_COOL_DOWN);
	isAttackOver = false;
}

void EnemyState_Attack::PlayerCollision()
{
	if (!isAttackOver)
	{
		VECTOR forward = ENEMY_ATTACK_COLL_POS_FROM_ENEMY_POS
			* MGetRotY(parent->GetRot().y);
		VECTOR atkCollPos = parent->GetPos() + forward;
		if (VSize(player->GetPos() - atkCollPos) <= ENEMY_ATTACK_COLL_DIST)
		{
			isAttackOver = true;
			float speed = ENEMY_ATTACK_KNOCK_BACK_SPEED;
			player->Damage(VGet(0, 0, speed) * MGetRotY(parent->GetRot().y));
		}
	}
}
