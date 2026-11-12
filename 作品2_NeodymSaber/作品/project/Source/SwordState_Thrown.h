#pragma once
#include "SwordStateBase.h"


/*
	投げられて飛んでいる剣ステートクラス
	綾部
*/

class SwordState_Thrown : public SwordStateBase
{
public:
	SwordState_Thrown() : firstPos(VZero) {}
	~SwordState_Thrown() {}
	void Update()override;
	void End()override;

private:
	VECTOR firstPos;
};