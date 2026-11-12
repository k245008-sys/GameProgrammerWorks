#include "SwordState_Held.h"
#include "SwordBase.h"

void SwordState_Held::Update()
{
	parent->SetVelocity(VZero);
}

void SwordState_Held::End()
{
}
