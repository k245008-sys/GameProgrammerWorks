#pragma once
#include "PlayerStateBase.h"

class EnemyBase;

/*
	攻撃前に目標へ接近するプレイヤーステートクラス
	綾部
*/

class PlayerState_Approach : public PlayerStateBase
{
public:
	PlayerState_Approach() {}
	~PlayerState_Approach() {}
	void Update()override;
	void End()override;
};