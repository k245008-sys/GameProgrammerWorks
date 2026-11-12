#pragma once
#include "EnemyState_IdleBase.h"

/*
	近・遠距離攻撃敵の待機ステートクラス
	綾部
*/

class EnemyState_Idle_Normal : public EnemyState_IdleBase
{
public:
	EnemyState_Idle_Normal() {}
	~EnemyState_Idle_Normal() {}
	void Update()override;
	void End()override;
};