#include "PlayScene.h"
#include "../Library/sceneManager.h"
#include "../Library//Time.h"
#include "debugScreen.h"
#include "Player.h"
#include "EnemyManager.h"
#include "StageManager.h"
#include "ShotManager.h"
#include "CollisionManager.h"
#include "OffScreenEnemyGuidManager.h"
#include "UiManager.h"
#include "Camera.h"
#include "Light.h"
#include "Debug.h"
#include "InputManager.h"
#include "SoundValue.h"
#include "EffectManager.h"
#include "ScoreManager.h"
#include"GameOver.h"
#include"ResultScene.h"
#include "Emitter.h"
#include <assert.h>
#include "RoundShadowManager.h"
#include "TitleScene.h"
#include "Fade.h"
#include "config.h"
#include "PlayerValue.h"

namespace
{
	// 目標フレーム数
	const int TARGET_FPS = 60;
	// 目標フレーム時間(秒)
	const float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;

	// 描画優先順(大きいほど優先)
	enum DrawOrder
	{
		D_SHADOW = 100,
		D_SHOT,
		D_STAGE,
		D_ENEMY,
		D_PLAYER,
		D_ENEMY_GUID,
		D_EMITTER,
		D_COLLISION,
		D_LIGHT,
		D_CAMARE,
		D_UI,
		D_DEBUG,
	};
}

PlayScene::PlayScene()
{
	shadowTexture = LoadGraph("data/model/Texture/roundShadow.png");
	assert(shadowTexture > 0);

	startImages.insert({"mission", LoadGraph("data/texture/gameStart_mission.png")});
	startImages.insert({ "start", LoadGraph("data/texture/gameStart_start.png") });
	for (auto& s : startImages)
		assert(s.second > 0);

	shadow = Instantiate<RoundShadowManager>();
	player = Instantiate<Player>();
	stageManager = Instantiate<StageManager>();
	enemyManager = Instantiate<EnemyManager>();
	shotManager = Instantiate<ShotManager>();
	collisionManager = Instantiate<CollisionManager>();
	enemyGuidManager = Instantiate<OffScreenEnemyGuidManager>();
	light = Instantiate<Light>();
	camera = Instantiate<Camera>();
	uiManager = Instantiate<UiManager>();
	debug = Instantiate<Debug>();
	emitter = Instantiate<Emitter>();
	SetDrawOrder(stageManager, D_STAGE);
	SetDrawOrder(uiManager, D_UI);
	SetDrawOrder(enemyGuidManager, D_ENEMY_GUID);
	SetDrawOrder(player, D_PLAYER);
	SetDrawOrder(enemyManager, D_ENEMY);
	SetDrawOrder(camera, D_CAMARE);
	SetDrawOrder(light, D_LIGHT);
	SetDrawOrder(debug, D_DEBUG);
	SetDrawOrder(shotManager, D_SHOT);
	SetDrawOrder(emitter, D_EMITTER);
	SetDrawOrder(shadow, D_SHADOW);

	gameover = new GameOver();
	result = new ResultScene();
	title = new TitleScene();

	Restart();
	sound->Stop("PlayBgm");
	state = TITLE;
}

PlayScene::~PlayScene()
{
	delete gameover;
	delete result;
	delete title;
	DeleteGameObject(player);
	DeleteGameObject(stageManager);
	DeleteGameObject(shotManager);
	DeleteGameObject(enemyGuidManager);
	DeleteGameObject(uiManager);
	DeleteGameObject(enemyManager);
	DeleteGameObject(collisionManager);
	DeleteGameObject(camera);
	DeleteGameObject(light);
	DeleteGameObject(debug);
	DeleteGameObject(emitter);
	DeleteGameObject(shadow);

	for (auto& s : startImages)
		DeleteGraph(s.second);
	startImages.clear();

	if (shadowTexture > 0)
		DeleteGraph(shadowTexture);

	sound->Stop("PlayBgm");

	StopJoypadVibration(DX_INPUT_PAD1);
}

void PlayScene::Update()
{
	InputManager* input = SceneManager::CommonScene()->FindGameObject<InputManager>();
	ScoreManager* score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();

	switch (state)
	{
	case TITLE:
		title->Update();
		break;
	case BEFORE:
		if (fadeRate > 0)
			fadeRate -= 0.1f;
		else
		{
			fadeRate = 0;
			time += Time::GameDeltaTime();
			if (time >= 0.8f)
			{
				state = PLAY;
				player->ChangeStateOnce("Idle");
			}
		}
	case PLAY:
		StartUI();
#ifdef _DEBUG
		if (input->IsKeyPushDown("R"))
		{
			Restart();
		}

		if (input->IsKeyPushDown("F"))
		{
			appearFps = appearFps ? false : true;
		}
#endif
		score->SetDoCountTime(true);

		// 現実の経過時間をラグとして加算
		lag += realDeltaTime;

		Time::SetGameDeltaTime(TARGET_FRAME_TIME * slowMotionRate);

		realDeltaTime = Time::RealDeltaTime();

		SlowMotion();

		UpdateGame();

		CalcFPS();

		isGameOver = (player->GetHP() <= 0);
		if (isGameOver)
		{
			if (overTime <= 0.0f)
			{
				state = GAMEOVER;
			}
			else
			{
				overTime -= Time::GameDeltaTime();
			}
		}
		break;
	case GAMEOVER:
		score->Reset();

		sound->Stop("PlayBgm");
		gameover->Update();

#ifdef _DEBUG
		if (input->IsKeyPushDown("2"))
		{
			state = PLAY;
			player->SetHp(6);
			overTime = 2.5f;
		}
#endif
		break;

	case RESULT:
		sound->Stop("PlayBgm");
		score->SetDoCountTime(false);

		result->Update();

#ifdef _DEBUG
		if (input->IsKeyPushDown("2"))
		{
			state = PLAY;
			player->SetHp(6);
		}
#endif
		break;
	}
}

void PlayScene::Draw()
{
	SceneBase::Draw();
	Color c = WHITE_C;
	DebugSetColor(c.r, c.g, c.b);
	SetFontSize(32);

	StartUIDraw();

	switch (state)
	{
	case TITLE:
		title->Draw();
		break;

	case BEFORE:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * fadeRate));
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	case GAMEOVER:
		gameover->Draw();
		break;

	case CLEAR:
		DrawGraph(0, 0, clearImage, true);
		break;

	case RESULT:
		result->Draw();
		break;
	}

#ifdef _DEBUG
	if(appearFps)
	DebugPrintf(0, 0,"fps : %.1f", fps);
#endif
}

void PlayScene::ChangeState(const PlayState& _state)
{
	if (_state == BEFORE)
	{
		Restart();
	}
	state = _state;
}

void PlayScene::Restart()
{
	state = BEFORE;
	fadeRate = 1.0f;
	time = 0;
	startTime = 0;
	uiPos = VECTOR2(1000, 0);
	alphaRate = 1.0f;
	uiSpeedX = 0.0f;
	appearTime = 0;

	ScoreManager* score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
	score->Reset();
	sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Play("PlayBgm", true);

	uiManager->SetEnable(true);
	enemyGuidManager->SetEnable(true);

	SetCameraPositionAndTarget_UpVecY(PLAYER_START_POS + CAMERA_DEF_POS, PLAYER_START_POS + CAMERA_DEF_TARGET_POS);
	player->Reset();
	enemyManager->Restart();
	camera->ResetCamera();
	stageManager->Restate();
	EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	effect->Reset();
	sound->Stop("ResultBgm");

	gameover->Reset();
	result->Reset();

	slowMotionTime = 0.0f;
	slowMotionRate = 1.0f;
	hitStopTime = 0.0f;
	lag = 0.0f;
	realDeltaTime = 0.0f;
	Time::SetGameDeltaTime(TARGET_FRAME_TIME);
	appearFps = false;
	fps = 0.0f;
	frameCount = 0;
	fpsTime = 0.0f;
	isGameOver = false;
	overTime = 2.5f;
}

void PlayScene::UpdateGame()
{
	// ヒットストップ
	if (hitStopTime > 0)
	{
		hitStopTime -= Time::GameDeltaTime();
		return;
	}

	// Update前に全クラスのFindを済ませる
	SceneBase::AssignFindObjToField();
	SceneBase::Update();	
}

void PlayScene::CalcFPS()
{
	frameCount++;
	fpsTime += realDeltaTime;
	if (fpsTime >= 1.0f)
	{
		fps = frameCount / fpsTime;
		frameCount = 0;
		fpsTime = 0.0f;
	}
}

void PlayScene::SlowMotion()
{
	// ヒットストップしていない時、スローモーション処理
	if (slowMotionTime > 0 && hitStopTime <= 0)
	{
		slowMotionTime -= realDeltaTime;
	}
	else
	{
		slowMotionRate = 1.0f;
		slowMotionTime = 0;
	}
}

void PlayScene::StartUI()
{
	if (alphaRate < 0)
		return;
	startTime += Time::GameDeltaTime();
	if (startTime < 0.1f)
		return;
	if (uiPos.x > 250)
	{
		uiPos.x -= uiSpeedX;
		uiSpeedX += 2.0f;
	}
	else
	{
		uiPos.x = 0;
		if (appearTime == 0)
			sound->Play("SnapUnion2");
		appearTime += Time::GameDeltaTime();
		if (appearTime >= 1.2f)
		{
			alphaRate -= 0.1f;
		}
	}
}

void PlayScene::StartUIDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * alphaRate));

	VECTOR2 adjust = VECTOR2(505, 150);
	float space = 505;
	DrawRectGraphF(adjust.x - uiPos.x - space, adjust.y + uiPos.y, 0, 0, 1010, 226, startImages["mission"], TRUE);
	DrawRectGraphF(adjust.x + uiPos.x + space, adjust.y + uiPos.y, 0, 0, 910, 226, startImages["start"], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
