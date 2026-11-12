#pragma once
#include "../Library/gameObject.h"
#include "CameraAdjustValue.h"
#include "StateBase.h"
#include "../Library/Time.h"

//カメラステートの基底クラス

class InputManager;
class Camera;
class Player;
class SwordBase;
class StateManager;
class StageManager;
class EnemyManager;

class CameraStateBase : public StateBase
{
public:

	CameraStateBase();
	virtual ~CameraStateBase() {};
	virtual void Update() override {};
	virtual void End() override {};	//Stateが終わる時の処理をする。

	virtual void AssignFindObjToField() override;

protected:

	//ポインター
	InputManager* inputManager;
	Camera* camera;
	Player* player;
	SwordBase* sword;
	StateManager* stateManager;
	StageManager* stageManager;
	EnemyManager* enemyManager;

	//遷移したかどうか
	bool isTraned;
};

