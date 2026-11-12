#pragma once
#include "../Library/gameObject.h"
#include "CameraAdjustValue.h"
#include "StateManager.h"
#include "Object3D.h"

//カメラの基底クラス

class StateManager;

class CameraBase : public GameObject
{
public:

	CameraBase();
	~CameraBase() {};
	virtual void Update() override;
	virtual void Draw() override;

	VECTOR GetPos() const { return transform.position; }	//位置参照用関数
	VECTOR GetRot() const { return transform.rotation;}		//角度参照用関数
	std::string GetCurrentStateName() { return stateManager->GetCurrentStateName(); }	//ステート参照用関数

	virtual void jugeState() = 0; //ステート判定用関数

protected:

	StateManager* stateManager; //ステートマネージャー用ポインター

	Transform transform; //位置、角度、サイズを含む構造
};