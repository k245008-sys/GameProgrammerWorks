#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤー死亡ステートクラス
	綾部
*/

class PlayerState_Dead : public PlayerStateBase
{
public:
	PlayerState_Dead() {}
	~PlayerState_Dead() {}
	void Update()override;
	void End()override;
};