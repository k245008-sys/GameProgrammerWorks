#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー剣投げステートクラス
	綾部
*/

class PlayerState_Throw : public PlayerStateBase
{
public:
	PlayerState_Throw() {}
	~PlayerState_Throw() {}
	void Update()override;
	void End()override;
};