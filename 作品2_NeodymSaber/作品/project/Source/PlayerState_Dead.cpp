#include "PlayerState_Dead.h"
#include "../Library/Time.h"
#include "Player.h"
#include "PlayerValue.h"
#include <string>
#include "UiManager.h"
#include "OffScreenEnemyGuidManager.h"
#include "SoundManager.h"

void PlayerState_Dead::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnimRand("Dead", PLAYER_ANIM_SETTING_DEAD);
		sound->Play("PlayerVoice_GameOver");
		parent->SetVelocity(VZero);

		UiManager* ui = FindGameObject<UiManager>();
		ui->SetEnable(false);
		OffScreenEnemyGuidManager* off = FindGameObject<OffScreenEnemyGuidManager>();
		off->SetEnable(false);
	}
	elapsedTime += Time::GameDeltaTime();

	if (parent->GetHP() > 0)
		nextStateName = "Idle";
}

void PlayerState_Dead::End()
{
}
