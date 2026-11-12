#pragma once
#include "EnemyState_IdleBase.h"

/*
	自爆敵の待機ステートクラス
	綾部
*/

class EnemyState_Idle_Bomb : public EnemyState_IdleBase
{
public:
	EnemyState_Idle_Bomb() {}
	~EnemyState_Idle_Bomb() {}
	void Update()override;
	void End()override;
};