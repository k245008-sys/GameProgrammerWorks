#pragma once
#include "EnemyState_IdleBase.h"

/*
	遠距離攻撃敵の待機ステートクラス
	綾部
*/

class EnemyState_Idle_LongRange : public EnemyState_IdleBase
{
public:
	EnemyState_Idle_LongRange() {}
	~EnemyState_Idle_LongRange() {}
	void Update()override;
	void End()override;
};