#pragma once
#include "../Library/myDxLib.h"

class SwordBase;

class CommonFunc_SwordState
{
public:
	void JudgeAndDoFall(const VECTOR& _velPos, float& _velocityY, const VECTOR& _firstPos,
		const VECTOR& _targetPos, const bool& _isDraw);
	MV1_COLL_RESULT_POLY IsCollStageObj(const VECTOR& _startPos, const VECTOR& _endPos);
	VECTOR GetThrowVelocity(const VECTOR& _pos);
	VECTOR GetDistToThrowTarget(const VECTOR& _pos);
};