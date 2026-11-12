#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤーゲーム開始ステートクラス
	綾部
*/

class PlayerState_WaitStart : public PlayerStateBase
{
public:
	PlayerState_WaitStart() {}
	~PlayerState_WaitStart() {}
	void Update()override;
	void End()override;
};