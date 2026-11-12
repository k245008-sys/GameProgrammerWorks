#include "PlayerState_Throw.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Sword_Throw.h"
#include "SoundManager.h"
#include "SoundValue.h"
#include "CommonFunc_PlayerState.h"

void PlayerState_Throw::Update()
{
	camera->RotationCamera();

	CommonFunc_PlayerState psFunc;
	if (psFunc.JudgeAvoid(this))
		return;

	if (elapsedTime == 0)
	{
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->Play("ThrowSword");
		parent->PlayAnim("Throw");
		parent->SetVelocityXZ(VZero);
	}
	elapsedTime += Time::GameDeltaTime();

	if (elapsedTime >= PLAYER_THROW_TIME)
	{
		nextStateName = "Idle";
	}
}

void PlayerState_Throw::End()
{
	parent->SetRotX(0);
}
