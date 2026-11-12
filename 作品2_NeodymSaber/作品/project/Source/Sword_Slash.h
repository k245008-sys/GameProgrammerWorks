#pragma once
#include "SwordBase.h"
#include "SwordState_Held.h"
#include "SwordState_Equipped.h"

/*
	è‚Å‚Á‚Äa‚é‚ªƒƒCƒ“‚ÌŒ•ƒNƒ‰ƒX
	ˆ»•”
*/

class Sword_Slash : public SwordBase
{
public:
	Sword_Slash();
	~Sword_Slash();
	void Update()override;
	void Draw()override;

	VECTOR GetCollBasePos();
	VECTOR GetCollRootPos();
	VECTOR GetCollTipPos();

private:
	MATRIX GetBaseRot() { return MGetRotZXY(GetFrameWorldRot("sword_blue_grp")); }

	SwordState_Held s_held;
	SwordState_Equipped s_equipped;

	bool appearColl;
};