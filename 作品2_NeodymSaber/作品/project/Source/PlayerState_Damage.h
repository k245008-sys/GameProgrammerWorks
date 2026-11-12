#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤーダメージステートクラス
	綾部
*/

class PlayerState_Damage : public PlayerStateBase
{
public:
	PlayerState_Damage() {}
	~PlayerState_Damage() {}
	void Update()override;
	void End()override;
};