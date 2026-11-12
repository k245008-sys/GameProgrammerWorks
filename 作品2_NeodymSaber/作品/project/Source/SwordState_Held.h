#pragma once
#include "SwordStateBase.h"

/*
	掴んで固定されている剣ステートクラス
	綾部
*/

class SwordState_Held : public SwordStateBase
{
public:
	SwordState_Held() {}
	~SwordState_Held() {}
	void Update()override;
	void End()override;
};