#include "CameraState_Snap.h"
#include "Player.h"
#include "Camera.h"

void CameraState_Snap::Update()
{
	VECTOR cPos = camera->GetPos();
	VECTOR cTarget = camera->GetNormalTarget();
	
	float cVelo = VSize(player->GetVelocity() * Time::GameDeltaTime()) - CAMERA_SNAP_ADJUST_VELOCITY;
	
	//遷移
	camera->TransitionPos(CAMERA_SNAP_TARGET_POS, cTarget, cVelo);
	camera->TransitionPos(CAMERA_SNAP_POS, cPos, cVelo);

	//位置と注視点をセット
	camera->SetNormalTarget(cTarget);
	camera->SetPos(cPos);
}

void CameraState_Snap::End()
{
	camera->FollowToPlayer(CAMERA_DEF_TARGET_POS, CAMERA_DEF_POS);
}
