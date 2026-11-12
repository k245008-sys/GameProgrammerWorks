#include "CameraState_Avoid.h"
#include "Player.h"
#include "Camera.h"

void CameraState_Avoid::Update()
{
	//’Ç]
	camera->FollowToPlayer(CAMERA_ATTACK_TARGET_POS, CAMERA_ATTACK_POS);
}
