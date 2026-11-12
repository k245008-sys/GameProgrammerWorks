#include "PlayerState_Snap.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Sword_Throw.h"
#include "Camera.h"
#include "CameraAdjustValue.h"

void PlayerState_Snap::Update()
{
	parent->SetIsInvincible(true);

	camera->RotationCamera();

	Sword_Throw* sw_throw = parent->GetSword_Throw();
	VECTOR swPos = sw_throw->GetPos();
	VECTOR dist = swPos - parent->GetPos();
	snapMove.SetDistance(dist);

	if (elapsedTime == 0)
	{
		parent->PlayAnim("Snap");
		snapMove.PlaySound_velFirst();
		snapMove.SetJudgeNearDist(PLAYER_SNAP_JUDGE_FINISH_DIST_ALREADY_NEAR,
			PLAYER_SNAP_JUDGE_NEAR_FINISH_DIST, PLAYER_SNAP_JUDGE_NEAR_DIST_RATE_ALREADY_NEAR);
	}

	elapsedTime += Time::GameDeltaTime();

	VECTOR snapVel = snapMove.CalcVelocity(PLAYER_SNAP_ADD_SPEED,
		PLAYER_SNAP_SPEED_MAX, PLAYER_SNAP_NEAR_FINISH_SPEED);
	parent->SetVelocity(snapVel);
	parent->SetRotY(atan2f(dist.x, dist.z));

	VECTOR setVel = VZero;
	if (snapMove.JudgeFinishAndGetFinishVel(setVel, parent->GetPos(), parent->GetVelocity(),
		swPos, PLAYER_SNAP_JUDGE_FINISH_DIST) || elapsedTime >= PLAYER_SNAP_CANCEL_TIME)
	{
		Camera* camera = FindGameObject<Camera>();
		camera->SetShakeCamera(CAMERA_SHAKE_RANGE_PLAYER_SNAP, CAMERA_SHAKE_SPEED_PLAYER_SNAP, CAMERA_SHAKE_TIME_PLAYER_SNAP);

		EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
		effect->Create("SnapUnionRed", swPos +
			EFFECT_ADJUST_SNAP_UNION_POS * MGetRotY(atan2f(dist.x, dist.z)),
			VGet(0, atan2f(dist.x, dist.z), 0));

		parent->SetVelocity(setVel);
		parent->SetIsSnap(true);
		parent->SetWasSnap(true);
		nextStateName = "Idle";
		sw_throw->ChangeState("ComeBack");
	}
}

void PlayerState_Snap::End()
{
	parent->SetIsInvincible(false);
	snapMove.Reset();
}
