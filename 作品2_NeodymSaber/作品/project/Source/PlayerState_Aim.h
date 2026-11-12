#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー剣投げエイムステートクラス
	綾部
*/

class PlayerState_Aim : public PlayerStateBase
{
public:
	PlayerState_Aim() {}
	~PlayerState_Aim() {}
	void Update()override;
	void Draw()override;
	void End()override;
};