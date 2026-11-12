#pragma once
#include "PlayerStateBase.h"
#include "SnapMove.h"

/*
	投げた剣へくっついていくプレイヤーステートクラス
	綾部
*/

class PlayerState_Snap : public PlayerStateBase
{
public:
	PlayerState_Snap() : snapMove(SnapMove()), judgeNearDist(0) {}
	~PlayerState_Snap() {}
	void Update()override;
	void End()override;

private:
	SnapMove snapMove;
	float judgeNearDist;
};