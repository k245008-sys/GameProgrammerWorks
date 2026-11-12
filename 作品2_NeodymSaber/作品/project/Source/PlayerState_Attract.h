#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤーが青剣を使って敵を引き寄せるステートクラス
	綾部
*/

class PlayerState_Attract : public PlayerStateBase
{
public:
	PlayerState_Attract() {}
	~PlayerState_Attract() {}
	void Update()override;
	void Draw()override;
	void End()override;
};