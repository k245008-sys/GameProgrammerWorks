#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー待機ステートクラス
	綾部
*/

class PlayerState_Idle : public PlayerStateBase
{
public:
	PlayerState_Idle() {}
	~PlayerState_Idle() {}
	void Update()override;
	void End()override;
};