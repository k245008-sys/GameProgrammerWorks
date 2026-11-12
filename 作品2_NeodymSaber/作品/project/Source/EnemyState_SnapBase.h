#pragma once
#include "EnemyStateBase.h"
#include "SnapMove.h"

/*
	敵のスナップ(プレイヤー剣の磁力にくっつく)ステートの基底クラス
	綾部
*/

class EnemyState_SnapBase : public EnemyStateBase
{
public:
	EnemyState_SnapBase() : snapMove(SnapMove()), isFirstSnap(false) {}
	~EnemyState_SnapBase() {}
	virtual void Update()override;
	virtual void End()override;

private:
	SnapMove snapMove;
	bool isFirstSnap;
	std::string dir;
	std::string lastWhatAttracted;
};