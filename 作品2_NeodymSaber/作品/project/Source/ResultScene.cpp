#include "ResultScene.h"
#include "../Library/myDxLib.h"
#include"InputManager.h"
#include <assert.h>
#include"time.h"
#include "../Library/Time.h"
#include "ScoreManager.h"
#include "ColorValue.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "UiValue.h"
#include "ScoreValue.h"
#include "playScene.h"
#include "SelectUi.h"
#include "config.h"

ResultScene::ResultScene()
{
	compImage = LoadGraph("data\\texture\\rizaruto_mcp-1.png");
	assert(compImage > 0);
	resultImage = LoadGraph("data\\texture\\result2.png");
	assert(resultImage > 0);

	rankImage[0] = LoadGraph("data/texture/rankC.png");
	rankImage[1] = LoadGraph("data/texture/rankB.png");
	rankImage[2] = LoadGraph("data/texture/rankA.png");
	rankImage[3] = LoadGraph("data/texture/rankS.png");

	numImage = LoadGraph("data/texture/num03.png");

	spaceImage = LoadGraph("data/texture/space.png");

	state = R_BLACKOUT;

	input = nullptr;
	score = nullptr;

	Reset();
}

ResultScene::~ResultScene()
{
	DeleteGraph(compImage);
	DeleteGraph(resultImage);
	for (int i = 0; i < 4; i++)
		DeleteGraph(rankImage[i]);
	DeleteGraph(numImage);
	DeleteGraph(spaceImage);

	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Stop("ResultBgm");
}

void ResultScene::Update()
{
	SelectUi* select = SceneManager::CommonScene()->FindGameObject<SelectUi>();
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	switch (state)
	{
	case R_BLACKOUT:
		if (alphaNum == 0)
		{
			SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
			sound->Play("ResultBgm", false);

			select->Reset();
		}

		alphaNum += 3;

		if (alphaNum > 160 || select->GetSelectInput())
		{
			alphaNum = 160;
			state = R_APPEAR;
		}

		break;

	case R_APPEAR:
		if (select->GetSelectInput())
		{
			scoreAlphaRate = 1.0f;
			rankingAlphaRate = 1.0f;
			state = R_SELECT;
		}

		if (scoreAlphaRate < 1.0f)
			scoreAlphaRate += 0.1f;
		else
		{
			scoreAlphaRate = 1.0f;
		}

		time += Time::GameDeltaTime();
		if (time >= 1.0f)
		{
			if (rankingAlphaRate < 1.0f)
				rankingAlphaRate += 0.05f;
			else
			{
				rankingAlphaRate = 1.0f;
				state = R_SELECT;
			}
		}
		break;

	case R_SELECT:
		select->UpdateSelect();
		break;

	default:
		break;
	}
}

void ResultScene::Draw()
{
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaNum);
	DrawBox(0, 0, 1920, 1080, 0x1f1f1f, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * scoreAlphaRate));
	float posY = -10.0f;
	DrawGraphF(0, posY, compImage, true);
	DrawGraphF(0, posY - 20.0f, resultImage, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * scoreAlphaRate));
	DrawResult();
	VECTOR2 center = VECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	score->DrawRanking(center + VECTOR2(-750, 320));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	switch (state)
	{
	case R_SELECT:
		SelectUi* select = SceneManager::CommonScene()->FindGameObject<SelectUi>();
		select->DrawSelect();
	}
}

void ResultScene::Reset()
{
	state = R_BLACKOUT;
	backalupa_num = 0;
	alphaNum = 0;
	scoreAlphaRate = 0;
	rankingAlphaRate = 0;
	time = 0;
}

void ResultScene::DrawResult()
{
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	float allY = -30.0f;

	// タイム
	// 分
	int time = (int)score->GetElapsedTime();
	time = (int)(time / 60.0f);
	int dig = 0;
	int copy = time;
	VECTOR2 pos = VECTOR2(1330, 500);
	while (copy > 0)
	{
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, copy % 10 * ONE_COMBO_FOTE_SIZEX, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
		copy /= 10;
		dig++;
	}
	if (time == 0)
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, 0, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);

	// :
	pos = VECTOR2(1372, 532);
	DrawGraphF(pos.x, pos.y + allY, spaceImage, true);

	// 秒(
	time = (int)score->GetElapsedTime();
	time = (int)(time % 60);
	dig = 0;
	copy = time;
	bool oneDig = (copy < 10);
	pos = VECTOR2(1480, 500);
	while (copy > 0)
	{
		if (oneDig)
		{
			DrawRectGraphF(pos.x - ONE_COMBO_FOTE_SIZEX, pos.y + allY, 0, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
			oneDig = false;
			continue;
		}
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, copy % 10 * ONE_COMBO_FOTE_SIZEX, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
		copy /= 10;
		dig++;
	}
	if (time == 0)
	{
		DrawRectGraphF(pos.x - ONE_COMBO_FOTE_SIZEX, pos.y + allY, 0, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
		DrawRectGraphF(pos.x, pos.y + allY, 0, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
	}

	// コンボ
	int comboNum = score->GetTotalCombo();
	dig = 0;
	copy = comboNum;
	pos = VECTOR2(1480, 379);
	while (copy > 0)
	{
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, copy % 10 * ONE_COMBO_FOTE_SIZEX, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
		copy /= 10;
		dig++;
	}
	if (comboNum == 0)
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, 0, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);

	// スコア
	int sc = score->GetScore();
	dig = 0;
	copy = sc;
	pos = VECTOR2(1490, 667);
	while (copy > 0)
	{
		DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y + allY, copy % 10 * ONE_COMBO_FOTE_SIZEX, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
		copy /= 10;
		dig++;
	}

	// ランク
	int rank = 0;
	if (sc <= C_RANK_SCORE)
		rank = 0;
	else if (sc <= B_RANK_SCORE)
		rank = 1;
	else if (sc <= A_RANK_SCORE)
		rank = 2;
	else
		rank = 3;
	pos = VECTOR2(170, 400);
	DrawGraphF(pos.x, pos.y, rankImage[rank], true);
}