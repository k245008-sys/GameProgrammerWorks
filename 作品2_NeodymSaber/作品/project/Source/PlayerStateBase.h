#pragma once
#include "StateBase.h"

/*
	プレイヤーステートの基底クラス
	綾部
*/

class InputManager;
class SoundManager;
class EffectManager;
class Player;
class Camera;	
class DynamicObjBase;

class PlayerStateBase : public StateBase
{
public:
	PlayerStateBase() : input(nullptr), sound(nullptr),effect(nullptr), parent(nullptr), camera(nullptr) {}
	virtual ~PlayerStateBase() {}
	virtual void Update()override {}
	virtual void End()override {}

	virtual void AssignFindObjToField()override;

	InputManager* GetInput() { return input; }
	Player* GetParent() { return parent; }
	Camera* GetCamera() { return camera; }

	void SetParent(DynamicObjBase* _parent)override;

protected:
	InputManager* input;
	SoundManager* sound;
	EffectManager* effect;
	Camera* camera;
	Player* parent;
};