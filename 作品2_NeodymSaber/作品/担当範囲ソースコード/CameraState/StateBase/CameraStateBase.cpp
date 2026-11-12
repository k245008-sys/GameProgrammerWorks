#include "CameraStateBase.h"
#include "InputManager.h"
#include "Camera.h"
#include "Player.h"
#include "SwordBase.h"
#include "EnemyManager.h"

CameraStateBase::CameraStateBase()
{
	inputManager = nullptr;
	camera = nullptr;
	player = nullptr;
	sword = nullptr;
	stateManager = nullptr;
	stageManager = nullptr;
	enemyManager = nullptr;

	isTraned = false;
}

void CameraStateBase::AssignFindObjToField()
{
	inputManager = SceneManager::CommonScene()->FindGameObject<InputManager>();
	camera = FindGameObject<Camera>();
	player = FindGameObject<Player>();
	sword = FindGameObject<SwordBase>();
	stateManager = FindGameObject<StateManager>();
	stageManager = FindGameObject<StageManager>();
	enemyManager = FindGameObject<EnemyManager>();
}


