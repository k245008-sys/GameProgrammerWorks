#include "PlayerState_Run.h"
#include "CommonFunc_PlayerState.h"
#include "InputManager.h"

void PlayerState_Run::Update()
{
	if (parent->GetPlayAnim() != "Run")
		parent->PlayAnim("Run");

	camera->RotationCamera();

	CommonFunc_PlayerState psFunc;
	float speed = PLAYER_RUN_SPEED_MAX;
	if (parent->GetEnableDebugSpeed())
		speed = PLAYER_DEBUG_RUN_SPEED;
	psFunc.SetRotYAndVelocityXZByCameraAndLStick(speed, this);
	VECTOR vel = parent->GetVelocity();
	if (VSize(vel) > 0 && VSize(vel) < PLAYER_RUN_SPEED_MIN)
		parent->SetVelocity(VNorm(vel) * PLAYER_RUN_SPEED_MIN);

	if (psFunc.JudgeAttack(this) ||
		psFunc.JudgeAttract(this) ||
		psFunc.JudgeAimOrSnap(this) ||
		psFunc.JudgeAvoid(this))
		return;
	if (!input->IsStickTiltOrKeyPushDir(false))
		nextStateName = "Idle";
}

void PlayerState_Run::End()
{
}
