#pragma once
#include "SwordStateBase.h"

/*
	地面に突き刺さっている剣ステートクラス
	綾部
*/

class SwordState_Pierced : public SwordStateBase
{
public:
	SwordState_Pierced() : attractDist(0) {}
	~SwordState_Pierced() {}
	void Update()override;
	void Draw()override;
	void End()override;

private:
	float attractDist;
};