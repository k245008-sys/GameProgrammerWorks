#include "TitleScene.h"
#include <assert.h>
#include "../Library/myDxLib.h"
#include "../Library/Time.h"
#include"InputManager.h"
#include"ScoreManager.h"
#include"time.h"
#include "SoundManager.h"
#include "playScene.h"
#include "config.h"

TitleScene::TitleScene()
{
	logoImage = LoadGraph("data\\texture\\logo.png");
	assert(logoImage > 0);
	BotanLogo = LoadGraph("data\\texture\\pushB.png");
	assert(BotanLogo > 0);
	backImage = LoadGraph("data/texture/back.png");

	Reset();
}

TitleScene::~TitleScene()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Stop("TitleBgm");
	if (BotanLogo > 0)
		DeleteGraph(BotanLogo);
	DeleteGraph(logoImage);
	DeleteGraph(backImage);
}

void TitleScene::Update()
{
	input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	bool start = input->IsPadPushDown("2");
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	switch (state)
	{
	case FADE_IN:
		if (fadeRate > 0)
			fadeRate -= 0.2f;
		else
		{
			fadeRate = 0;
			state = WAIT;
		}
		break;

	case WAIT:
		velocity += DegToRad(80.0f * (1.0f / 60.0f));
		if (!sound->IsPlay("TitleBgm"))
			sound->Play("TitleBgm", false);
#ifdef _DEBUG
		if (input->IsKeyPushDown("2"))
			start = true;
#endif
		if (start)
		{
			sound->Play("Start");
			state = FADE_OUT;
		}
		break;

	case FADE_OUT:
		if (fadeRate < 1.0f)
			fadeRate += 0.05f;
		else
		{
			fadeRate = 1.0f;
			time += Time::GameDeltaTime();
			if (time >= 0.5f)
			{
				sound->Stop("TitleBgm");
				SceneBase* scene = SceneManager::CurrentScene();
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				pScene->ChangeState(PlayState::BEFORE);
				Reset();
			}
		}
		break;

	default:
		break;
	}
}

void TitleScene::Draw()
{
	DrawGraphF(0, 0, backImage, true);
	DrawGraphF(20, 0, logoImage, true);
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	score->DrawRanking(VECTOR2(250, 1015));

	if (state == WAIT)
	{
		float prm = 12.0f * abs(cosf(velocity));
		prm = abs(cosf(velocity)) * 300.0f;
		if (prm > 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)prm);
			DrawGraph(0, -10, BotanLogo, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * fadeRate));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Reset()
{
	state = FADE_IN;
	fadeRate = 1.0f;
	time = 0;
	scale = 2.0f;
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	score->Reset();
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Stop("TitleBgm");
}
