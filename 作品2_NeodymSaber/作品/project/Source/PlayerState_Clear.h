#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤークリア時のステートクラス
	綾部
*/

class PlayerState_Clear : public PlayerStateBase
{
public:
	PlayerState_Clear() {}
	~PlayerState_Clear() {}
	void Update()override;
	void End()override;
};