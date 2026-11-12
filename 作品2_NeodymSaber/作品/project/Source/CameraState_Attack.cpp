#include "CameraState_Attack.h"
#include "Camera.h"
#include "Player.h"

void CameraState_Attack::Update()
{
	//’Ç]‚³‚¹‚é
	camera->FollowToPlayer(CAMERA_ATTACK_TARGET_POS, CAMERA_ATTACK_POS);
}

void CameraState_Attack::End()
{
	
}