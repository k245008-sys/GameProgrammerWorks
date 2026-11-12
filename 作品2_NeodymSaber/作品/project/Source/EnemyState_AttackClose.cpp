#include "EnemyState_AttackClose.h"
#include "Player.h"
#include "EnemyValue.h"
#include "EnemyBase.h"
#include "CommonFunc_EnemyState.h"
#include "SoundManager.h"
#include "SoundValue.h"
#include "DrawBox3D.h"

void EnemyState_AttackClose::Update()
{
	VECTOR dist = player->GetPos() - parent->GetPos();
	if (elapsedTime == 0)
	{
		sound->Play("EnemyAttackWarning");
		parent->PlayAnim("AttackClose");
		firstDist = dist;
	}
	elapsedTime += Time::GameDeltaTime();

	parent->MoveRotY(ENEMY_ATTACK_vel_ROT_Y_SPEED, atan2f(firstDist.x, firstDist.z));
	if (elapsedTime < ENEMY_BEFORE_ATTACK_TIME)
	{
		if (elapsedTime < ENEMY_BEFORE_ATTACK_BLINKING_TIME * 4)
		{
			blinkingTimer += Time::GameDeltaTime();
			if (blinkingTimer >= ENEMY_BEFORE_ATTACK_BLINKING_TIME * 2)
				blinkingTimer = 0;
		}
		parent->SetVelocityXZ(VZero);
	}
	else if (elapsedTime < ENEMY_BEFORE_ATTACK_TIME +
		ENEMY_ATTACK_FORWARD_TIME)
	{
		parent->SetVelocityXZ(VNorm(firstDist) * ENEMY_ATTACK_FORWARD_SPEED);
		if (!playedSound)
		{
			sound->Play("EnemyAttack_CloseRange");
			playedSound = true;
		}
	}
	else
	{
		parent->ChangeState("Idle");
		return;
	}

	if (elapsedTime >= ENEMY_ATTACK_COLL_TIMING_START && 
		elapsedTime < ENEMY_ATTACK_COLL_TIMING_END)
	{
		PlayerCollision();
	}
	if (isAttackOver)
		parent->ChangeState("Idle");
}

void EnemyState_AttackClose::Draw()
{
	if (elapsedTime >= ENEMY_BEFORE_ATTACK_TIME)
		return;

	unsigned int color = ENEMY_ATTACK_DRAW_WARNING_COLOR;
	if (blinkingTimer >= ENEMY_BEFORE_ATTACK_BLINKING_TIME)
		color = YELLOW;

	DrawBox3D box3D;
	box3D.DrawFront(parent->GetPos(),
		VGet(ENEMY_ATTACK_DRAW_WARNING_SIZE.x, ENEMY_ATTACK_DRAW_WARNING_SIZE.y,
			ENEMY_ATTACK_FORWARD_SPEED * ENEMY_ATTACK_FORWARD_TIME), VGet(0, parent->GetRot().y, 0),
		color, ENEMY_ATTACK_DRAW_WARNING_ALPHA);
}

void EnemyState_AttackClose::End()
{
	isAttackOver = false;
	blinkingTimer = 0;
	playedSound = false;
	if (parent == nullptr)
		return;
	parent->SetAttackCoolDown(ENEMY_ATTACK_COOL_DOWN);
	if (nextStateName == "Idle")
		parent->SetAnimBlendFrame("Idle", ENEMY_ANIM_AFTER_ATTACK_CLOSE_IDLE_BLEND_FRAME);
}

void EnemyState_AttackClose::PlayerCollision()
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
