#pragma once
#include "EnemyStateBase.h"

/*
	敵ダメージステートクラス
	綾部
*/

class EnemyState_Damage : public EnemyStateBase
{
public:
	EnemyState_Damage() : playAnim(false) {}
	~EnemyState_Damage() {}
	void Update()override;
	void End()override;

private:
	bool playAnim;
};