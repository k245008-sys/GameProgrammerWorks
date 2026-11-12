#pragma once
#include "EnemyStateBase.h"

/*
	敵待機ステートクラス
	綾部
*/

class EnemyState_Idle : public EnemyStateBase
{
public:
	EnemyState_Idle() {}
	~EnemyState_Idle() {}
	void Update()override;
	void End()override;
};