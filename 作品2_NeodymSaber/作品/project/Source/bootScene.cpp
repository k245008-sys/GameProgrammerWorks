#include "bootScene.h"
#include "../Library/sceneManager.h"
#include "debugScreen.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "ScoreManager.h"
#include "SelectUi.h"

BootScene::BootScene()
{
	SceneBase* common = SceneManager::CommonScene();
	DebugScreen* ds = common->CreateGameObject<DebugScreen>();
	InputManager* input = common->CreateGameObject<InputManager>();
	SoundManager* sound = common->CreateGameObject<SoundManager>();
	EffectManager* effect = common->CreateGameObject<EffectManager>();
	SelectUi* select = common->CreateGameObject<SelectUi>();
	ScoreManager* score = common->CreateGameObject<ScoreManager>();
	common->SetDrawOrder(ds, 10000);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("PlayScene");
}

void BootScene::Draw()
{
}
