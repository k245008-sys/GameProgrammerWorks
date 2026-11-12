#pragma once
#include "EnemyState_IdleBase.h"

/*
	近距離攻撃敵の待機ステートクラス
	綾部
*/

class EnemyState_Idle_CloseRange : public EnemyState_IdleBase
{
public:
	EnemyState_Idle_CloseRange() {}
	~EnemyState_Idle_CloseRange() {}
	void Update()override;
	void End()override;
};