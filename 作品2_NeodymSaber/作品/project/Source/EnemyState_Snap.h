#pragma once
#include "EnemyState_SnapBase.h"

/*
	敵のスナップ(プレイヤー剣の磁力にくっつく)ステートクラス
	綾部
*/

class EnemyState_Snap : public EnemyState_SnapBase
{
public:
	EnemyState_Snap() {}
	~EnemyState_Snap() {}
	void Update()override;
	void End()override;
};