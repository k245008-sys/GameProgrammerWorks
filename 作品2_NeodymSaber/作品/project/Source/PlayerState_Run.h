#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー移動ステートクラス
	綾部
*/

class PlayerState_Run : public PlayerStateBase
{
public:
	PlayerState_Run() {}
	~PlayerState_Run() {}
	void Update()override;
	void End()override;
};