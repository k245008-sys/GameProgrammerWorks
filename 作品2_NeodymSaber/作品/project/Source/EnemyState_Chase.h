#pragma once
#include "EnemyStateBase.h"

/*
	敵プレイヤー追跡ステートクラス
	綾部
*/

class EnemyState_Chase : public EnemyStateBase
{
public:
	EnemyState_Chase() {}
	~EnemyState_Chase() {}
	virtual void Update()override;
	virtual void End()override;
};