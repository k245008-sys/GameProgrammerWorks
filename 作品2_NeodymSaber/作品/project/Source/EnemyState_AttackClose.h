#pragma once
#include "../Library/myDxLib.h"
#include "EnemyStateBase.h"

/*
	敵攻撃ステートクラス
	綾部
*/

class EnemyState_AttackClose : public EnemyStateBase
{
public:
	EnemyState_AttackClose() : isAttackOver(false), firstDist(VZero), blinkingTimer(0), playedSound(false) {}

	~EnemyState_AttackClose() {}
	void Update()override;
	void Draw()override;
	void End()override;

	void PlayerCollision();

private:
	VECTOR firstDist;
	bool isAttackOver;
	float blinkingTimer;
	bool playedSound;
};