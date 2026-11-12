#include "SwordState_Equipped.h"
#include "Sword_Throw.h"
#include "SwordValue.h"

void SwordState_Equipped::Update()
{
	parent->SetVelocity(VZero);
}

void SwordState_Equipped::End()
{
}
