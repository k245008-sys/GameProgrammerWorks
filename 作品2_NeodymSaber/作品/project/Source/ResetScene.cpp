#include "ResetScene.h"
#include "EffectManager.h"

ResetScene::ResetScene()
{
}

ResetScene::~ResetScene()
{
}

void ResetScene::Update()
{
	EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	effect->Reset();

	SceneManager::ChangeScene("PlayScene");
}

void ResetScene::Draw()
{
}
