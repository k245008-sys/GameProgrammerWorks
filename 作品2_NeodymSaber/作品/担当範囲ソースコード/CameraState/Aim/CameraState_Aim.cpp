#include "CameraState_Aim.h"
#include "Camera.h"
#include "Player.h"

void CameraState_Aim::Update()
{
	VECTOR cTarget = camera->GetNormalTarget();
	VECTOR cPos = camera->GetPos();
	
	if (isTraned == false)
	{
		//‘JˆÚ‚³‚¹‚é
		if (camera->TransitionPos(CAMERA_AIM_TARGET_POS, cTarget, CAMERA_AIM_TRANS_SPEED) == true &&
			camera->TransitionPos(CAMERA_AIM_POS, cPos, CAMERA_AIM_TRANS_SPEED) == true)
		{
			isTraned = true;
		}

		//ˆÊ’u‚Æ’Ž‹“_‚ðƒZƒbƒg
		camera->SetNormalTarget(cTarget);
		camera->SetPos(cPos);

	}
	else
	{
		//‘JˆÚ‚ªI‚í‚Á‚½‚ç’Ç]
		camera->FollowToPlayer(CAMERA_AIM_TARGET_POS, CAMERA_AIM_POS);
	}
}

void CameraState_Aim::End()
{
	isTraned = false;
}