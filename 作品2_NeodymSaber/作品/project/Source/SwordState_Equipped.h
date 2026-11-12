#pragma once
#include "SwordStateBase.h"

/*
	装着によって固定された剣のステートクラス
	綾部
*/

class SwordState_Equipped : public SwordStateBase
{
public:
	SwordState_Equipped() {}
	~SwordState_Equipped() {}
	void Update()override;
	void End()override;
};