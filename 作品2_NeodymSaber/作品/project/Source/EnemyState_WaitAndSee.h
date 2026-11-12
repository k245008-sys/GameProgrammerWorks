#pragma once
#include "EnemyStateBase.h"
#include "../Library/myDxLib.h"

/*
	敵の様子見ステート基底クラス
	綾部
*/

class EnemyState_WaitAndSee : public EnemyStateBase
{
public:
	EnemyState_WaitAndSee() : changeDirTime(0),
	direction(0), chancePercent(0), distToPlayer(VZero) {}
	~EnemyState_WaitAndSee() {}
	virtual void Update()override;
	virtual void End()override;

private:
	void SetDirectionToBesideOrStay();
	void SetDirectionByChance();
	void SetVelocity();
	bool JudgeChangeDirection();
	void PlayAnim();

	enum DIRECTION
	{
		RIGHT,
		LEFT,
		FRONT,
		BACK,
		STAY,
		MAX_NUM,
	};

	VECTOR distToPlayer;
	float changeDirTime;
	int direction;
	int chancePercent;
};