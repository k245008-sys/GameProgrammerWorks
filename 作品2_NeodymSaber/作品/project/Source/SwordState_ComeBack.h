#pragma once
#include "SwordStateBase.h"

/*
	持ち主へ戻っていく剣ステートクラス
	綾部
*/

class SwordState_ComeBack : public SwordStateBase
{
public:
	SwordState_ComeBack() {}
	~SwordState_ComeBack() {}
	void Update()override;
	void End()override;
};