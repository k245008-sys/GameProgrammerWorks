#include "PlayerState_Idle.h"
#include "Player.h"
#include "InputManager.h"
#include "CommonFunc_PlayerState.h"
#include "playScene.h"

void PlayerState_Idle::Update()
{
	camera->RotationCamera();

	if (parent->GetPlayAnim() != "Idle")
		parent->PlayAnim("Idle");

	if(parent->GetIsGround())
		parent->SetVelocity(VZero);
	else
		parent->SetVelocityXZ(VZero);

	if (input->IsStickTiltOrKeyPushDir(false))
		nextStateName = "Run";
	CommonFunc_PlayerState psFunc;
	psFunc.JudgeAttack(this);
	psFunc.JudgeAttract(this);
	psFunc.JudgeAimOrSnap(this);
	psFunc.JudgeAvoid(this);
}

void PlayerState_Idle::End()
{
	parent->ResetAnimBlendFrame("Idle");
}
