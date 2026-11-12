#pragma once
#include "EnemyState_SnapBase.h"

/*
	敵のプレイヤー磁力範囲に固定されているステートクラス
	綾部
*/

class EnemyState_AttractedAndFixed : public EnemyState_SnapBase
{
public:
	EnemyState_AttractedAndFixed() {}
	~EnemyState_AttractedAndFixed() {}
	void Update()override;
	void End()override;
};