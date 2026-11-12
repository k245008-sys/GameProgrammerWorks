#include "PlayerState_Damage.h"
#include "Player.h"
#include "PlayerValue.h"
#include "SoundManager.h"
#include "SoundValue.h"
#include "Camera.h"
#include "CharaValue.h"
#include "InputManager.h"
#include "VibrationValue.h"

void PlayerState_Damage::Update()
{
	camera->RotationCamera();

	if (elapsedTime == 0)
	{
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->Play("PlayerDamage");
		sound->Play("PlayerVoice_Damage_Small");
		parent->PlayDamageAnim();

		if (input->GetEnableVib())
		StartJoypadVibration(DX_INPUT_PAD1, VIBRATION_POWER_PLAYER_DAMAGE, VIBRATION_TIME_PLAYER_DAMAGE);
	}
	elapsedTime += Time::GameDeltaTime();

	parent->MoveVelocityXZ(PLAYER_DAMAGE_REDUCE_SPEED, VZero);

	if (elapsedTime >= PLAYER_DAMAGE_TIME)
	{
		nextStateName = "Idle";
	}
}

void PlayerState_Damage::End()
{
	parent->SetInvincibleTime(PLAYER_AFTER_DAMAGE_INVINCIBLE_TIME);
}
