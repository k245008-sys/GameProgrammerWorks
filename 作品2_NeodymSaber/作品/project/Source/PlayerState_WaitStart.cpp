#include "PlayerState_WaitStart.h"
#include "Player.h"

void PlayerState_WaitStart::Update()
{
	if (parent->GetPlayAnim() != "Idle")
		parent->PlayAnim("Idle");

	parent->SetVelocityXZ(VZero);
}

void PlayerState_WaitStart::End()
{
}
