#pragma once
#include "EnemyStateBase.h"

/*
	敵のプレイヤーが来るまで待つステートクラス
	綾部
*/

class EnemyState_WaitStart : public EnemyStateBase
{
public:
	EnemyState_WaitStart() {}
	~EnemyState_WaitStart() {}
	void Update()override;
	void End()override;
};