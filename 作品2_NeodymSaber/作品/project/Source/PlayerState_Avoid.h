#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー回避ステートクラス
	綾部
*/

class PlayerState_Avoid : public PlayerStateBase
{
public:
	PlayerState_Avoid() : speed(0) {}
	~PlayerState_Avoid() {}
	void Update()override;
	void End()override;

private:
	float speed;
};