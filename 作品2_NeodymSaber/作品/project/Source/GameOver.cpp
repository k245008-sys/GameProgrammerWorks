#include "GameOver.h"
#include"ScoreManager.h"
#include"InputManager.h"
#include <assert.h>
#include "../Library/Time.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "playScene.h"
#include "SelectUi.h"

GameOver::GameOver()
{
	hImage[GAMEOVER_FOTE] = LoadGraph("data\\texture\\gameover_misson_unco-1.png");
	assert(hImage[GAMEOVER_FOTE] > 0);

	hImage[FLAME_LEFT] = LoadGraph("data\\texture\\gameover_fleam2-1.png");
	assert(hImage[FLAME_LEFT] > 0);

	hImage[FLAME_RIGHT] = LoadGraph("data\\texture\\gameover_fleam2-2.png");
	assert(hImage[FLAME_RIGHT] > 0);

	hImage[FADE_FOTE] = LoadGraph("data\\texture\\gameover_Blackout-1.png");
	assert(hImage[FADE_FOTE] > 0);

	Reset();
}

GameOver::~GameOver()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Stop("GameOverBgm");
	for (int i = 0; i < (int)(sizeof(hImage) / sizeof(hImage[0])); i++)
	{
		if (hImage[i] > 0)
		{
			DeleteGraph(hImage[i]);
		}
	}
}

void GameOver::Update()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	if (!sound->IsPlay("GameOverBgm"))
	{
		sound->Play("GameOverBgm", false);
	}

	SelectUi* select = SceneManager::CommonScene()->FindGameObject<SelectUi>();
	switch (state)
	{
	case STAGING:
		if (scaletime.y > 0.0f)
		{
			scaletime.y -= Time::GameDeltaTime();

			alpha_Num += 3;
			backalupa_Num += 3;
			blackalupa_Num += 3;

			select->Reset();
		}
		else
			state = SELECT;

		scaletime.x -= Time::GameDeltaTime();

		if (select->GetSelectInput())
		{
			scaletime.x = -2.0f;
			scaletime.y = 0;

			alpha_Num = 255;
			backalupa_Num = 255;
			blackalupa_Num = 255;

			state = SELECT;
		}
		if (backalupa_Num > 150)
		{
			backalupa_Num = 150;
		}

		if (alpha_Num > 175)
		{
			blackalupa_Num = 175;
		}

		if (alpha_Num > 255)
		{
			alpha_Num = 255;
		}
		break;

	case SELECT:
		select->UpdateSelect();
		break;

	default:
		break;
	}
}

void GameOver::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, backalupa_Num);
	DrawBox(0, 0, 1920, 1080, 0xFFFFFF, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackalupa_Num);
	DrawRectGraph(0, 0, 0, 0, 1920, 1080, hImage[FADE_FOTE], true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	float yscale = 968;

	float ratey = scaletime.y / 2.0f;

	float skaley = ratey * yscale;

	float newscaley = 0 - skaley;

	float xscale = 960;

	float rate = scaletime.x / 2.0f;

	float skale = rate * xscale;

	float newscale = 0 - skale;

	DrawRectGraphF(0, 20, (int)newscaley, 0, 960, 1080, hImage[FLAME_LEFT], true, false);

	DrawRectGraphF(960.0f, 20, 0, 0, (int)newscale, 1080, hImage[FLAME_RIGHT], true, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_Num);
	DrawRectGraph(0, 20, 0, 0, 1920, 1080, hImage[GAMEOVER_FOTE], true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	switch (state)
	{
	case SELECT:
		SelectUi* select = SceneManager::CommonScene()->FindGameObject<SelectUi>();
		select->DrawSelect();
	}
}

void GameOver::Reset()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Stop("GameOverBgm");

	velocity = 0.0f;

	scaletime.x = 0.0f;
	scaletime.y = 2.0f;

	blackalupa_Num = 0;
	alpha_Num = 0;
	backalupa_Num = 0;

	state = STAGING;
}