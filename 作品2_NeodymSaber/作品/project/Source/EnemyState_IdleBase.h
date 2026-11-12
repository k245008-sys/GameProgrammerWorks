#pragma once
#include "EnemyStateBase.h"

/*
	敵待機ステート基底クラス
	綾部
*/

class EnemyState_IdleBase : public EnemyStateBase
{
public:
	EnemyState_IdleBase() : waiting(false) {}
	~EnemyState_IdleBase() {}
	virtual void Update()override;
	virtual void End()override;

protected:
	bool waiting;
};