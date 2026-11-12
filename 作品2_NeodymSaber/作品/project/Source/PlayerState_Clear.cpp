#include "PlayerState_Clear.h"
#include "PlayerValue.h"
#include "Player.h"
#include "playScene.h"
#include "SoundManager.h"
#include "UiManager.h"
#include "OffScreenEnemyGuidManager.h"
#include "SoundValue.h"

void PlayerState_Clear::Update()
{
	parent->SetIsInvincible(true);

	if (elapsedTime == 0)
	{
		UiManager* ui = FindGameObject<UiManager>();
		ui->SetEnable(false);
		OffScreenEnemyGuidManager* off = FindGameObject<OffScreenEnemyGuidManager>();
		off->SetEnable(false);
	}

	parent->SetVelocity(VZero);
	std::string curAnim = parent->GetCurrentAnim();
	if (curAnim != "Clear")
	{
		if (parent->GetIsAnimFinish() || curAnim == "Idle" || curAnim == "Run")
		{
			parent->PlayAnim("Clear");
		}
		return;
	}

	float prevTime = elapsedTime;
	elapsedTime += Time::GameDeltaTime();

	if (elapsedTime >= PLAYER_CLEAR_VOICE_TIMING && prevTime < PLAYER_CLEAR_VOICE_TIMING)
		sound->Play("PlayerVoice_Clear");

	if (elapsedTime >= PLAYER_CLEAR_TIME)
	{
		SceneBase* scene = SceneManager::CurrentScene();
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		pScene->ChangeState(PlayState::RESULT);
	}
}

void PlayerState_Clear::End()
{
	parent->SetIsInvincible(false);
}
