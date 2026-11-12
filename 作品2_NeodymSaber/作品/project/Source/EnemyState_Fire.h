#pragma once
#include "EnemyStateBase.h"

/*
	敵の弾発射ステートクラス
	綾部
*/

class EnemyState_Fire : public EnemyStateBase
{
public:
	EnemyState_Fire() : playedSound(false) {}
	~EnemyState_Fire() {}
	void Update()override;
	void End()override;

private:
	bool playedSound;
};