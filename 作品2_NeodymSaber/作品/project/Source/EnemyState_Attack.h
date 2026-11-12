#pragma once
#include "EnemyStateBase.h"

/*
	敵攻撃ステートクラス
	綾部
*/

class EnemyState_Attack : public EnemyStateBase
{
public:
	EnemyState_Attack() : isAttackOver(false), firstDist(VGet(0,0,0)), blinkingTimer(0) {}
	~EnemyState_Attack() {}
	void Update()override;
	void End()override;

	void PlayerCollision();

private:
	VECTOR firstDist;
	bool isAttackOver;
	float blinkingTimer;
};