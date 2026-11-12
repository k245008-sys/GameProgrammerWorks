#pragma once
#include "../Library/myDxLib.h"
#include "EnemyStateBase.h"

/*
	敵のプレイヤーを狙うステートクラス
	綾部
*/

class Object3D;

class EnemyState_Aim : public EnemyStateBase
{
public:
	EnemyState_Aim() : isWarning(false), blinkingTimer(0) {}
	~EnemyState_Aim() {}
	void Update()override;
	void Draw()override;
	void End()override;

	MV1_COLL_RESULT_POLY CollideLineBetweenPlayer(Object3D* _stageObj, const float& _length,
		VECTOR* _retStartPos, VECTOR* _retEndPos);

private:
	bool isWarning;
	float blinkingTimer;
};