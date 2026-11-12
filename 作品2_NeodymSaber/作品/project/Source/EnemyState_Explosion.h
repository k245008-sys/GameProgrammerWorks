#pragma once
#include "EnemyStateBase.h"

/*
	敵爆発(自爆)ステートクラス
	綾部
*/

class EnemyState_Explosion : public EnemyStateBase
{
public:
	EnemyState_Explosion() {}
	~EnemyState_Explosion() {}
	void Update()override;
	void End()override;
};