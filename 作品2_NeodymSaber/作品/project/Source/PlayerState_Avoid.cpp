#include "PlayerState_Avoid.h"
#include "PlayerValue.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "SoundManager.h"
#include "MoveNum.h"

void PlayerState_Avoid::Update()
{
	parent->SetIsInvincible(true);

	camera->RotationCamera();

	if (elapsedTime == 0)
	{
		sound->Play("PlayerAvoid1");
		sound->Play("PlayerAvoid2");
		sound->Play("PlayerVoice_Avoid");

		parent->PlayAnim("Avoid");
		if (input->IsStickTilt("L"))
		{
			float angle = camera->GetRot().y + input->GetStickAngle("L");
			parent->SetRotY(angle);
		}
		speed = PLAYER_AVOID_SPEED;
		parent->SetAvoidCoolDown(PLAYER_AVOID_COOL_DOWN);
	}
	elapsedTime += Time::GameDeltaTime();

	parent->SetVelocityXZ(VGet(0, 0, speed) * MGetRotY(parent->GetRot().y));
	MoveNum moveNum;
	moveNum.SubToTarget<float>(speed, PLAYER_AVOID_REDUCE_SPEED, 0);

	if (elapsedTime >= PLAYER_AVOID_TIME)
		nextStateName = "Idle";
}

void PlayerState_Avoid::End()
{
	parent->SetInvincibleTime(PLAYER_AFTER_AVOID_INVINCIBLE_TIME);
}
