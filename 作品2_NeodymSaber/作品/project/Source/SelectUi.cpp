#include "SelectUi.h"
#include <assert.h>
#include "InputManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "playScene.h"
#include "config.h"
#include "../Library/Time.h"

SelectUi::SelectUi(SceneBase* _scene)
{
	hImages.insert({ "Retry", LoadGraph("data/texture/select_retry.png") });
	hImages.insert({ "Title", LoadGraph("data/texture/select_title.png") });
	hImages.insert({ "Back", LoadGraph("data/texture/selectBack.png") });
	hImages.insert({ "White", LoadGraph("data/texture/selectWhite.png") });
	for (auto& i : hImages)
		assert(i.second > 0);

	input = nullptr;
	Reset();
}

SelectUi::~SelectUi()
{
	for (auto& i : hImages)
		DeleteGraph(i.second);
	hImages.clear();
}

void SelectUi::UpdateSelect()
{
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	if (input->IsPadPushDown("Left") && state != S_RETRY)
	{
		state = S_RETRY;
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->Play("Cursor");
	}
	else if (input->IsPadPushDown("Right") && state != S_TITLE)
	{
		state = S_TITLE;
		SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
		sound->Play("Cursor");
	}

	time += Time::GameDeltaTime();
	if (time < 0.8f)
		return;

	bool push = GetSelectInput();
	if (push)
		go = true;
	switch (state)
	{
	case SelectState::S_RETRY:
		if (go)
		{
			if (alphaRate == 0)
			{
				SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
				sound->Play("Push");
				EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
				effect->Reset();
			}
			if (alphaRate < 1.0f)
				alphaRate += 0.1f;
			else
			{
				time += Time::GameDeltaTime();
				if (time >= 0.2f)
				{
					SceneBase* scene = SceneManager::CurrentScene();
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					pScene->Restart();
					state = S_TITLE;
				}
			}
		}
		break;

	case SelectState::S_TITLE:
		if (go)
		{
			if (alphaRate == 0)
			{
				SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
				sound->Play("Push");
			}
			if (alphaRate < 1.0f)
				alphaRate += 0.1f;
			else
			{
				time += Time::GameDeltaTime();
				if (time >= 0.2f)
				{
					SceneBase* scene = SceneManager::CurrentScene();
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					pScene->ChangeState(PlayState::TITLE);
				}
			}
		}
		break;
	}
}

void SelectUi::DrawSelect()
{
	VECTOR2 pos = VECTOR2(350, 455);
	VECTOR2 center = VECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	pos.y += center.y;
	DrawRotaGraphF(center.x - pos.x, pos.y, 1.0, 0.0, hImages["Back"], true);
	DrawRotaGraphF(center.x - pos.x, pos.y, 1.0, 0.0, hImages["Retry"], true);

	DrawRotaGraphF(center.x + pos.x, pos.y, 1.0, 0.0, hImages["Back"], true);
	DrawRotaGraphF(center.x + pos.x, pos.y, 1.0, 0.0, hImages["Title"], true);
	
	int sign = 1;
	if (state == S_TITLE)
		sign = -1;
	int bri = 100;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	SetDrawBright(bri, bri, bri);
	DrawRotaGraphF(center.x + pos.x * sign, pos.y, 1.0, 0.0, hImages["White"], true);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * alphaRate));
	DrawBox(0, 0, 1920, 1080, 0x1f1f1f, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SelectUi::GetSelectInput()
{
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	return input->IsPadPushDown("2");
}

void SelectUi::Reset()
{
	state = S_TITLE;
	time = 0;
	go = false;
	alphaRate = 0;
}
