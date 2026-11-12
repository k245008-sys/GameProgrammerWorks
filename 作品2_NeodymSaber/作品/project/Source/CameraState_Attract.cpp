#include "CameraState_Attract.h"
#include "Camera.h"

void CameraState_Attract::Update()
{
	VECTOR cTarget = camera->GetNormalTarget();
	VECTOR cPos = camera->GetPos();
	
	if (camera->GetBeforeStateName() != "AttractAttack")
	{
		if (isTraned == false)
		{
			//‘JˆÚ‚³‚¹‚é
			if (camera->TransitionPos(CAMERA_ATTRACT_TARGET_POS, cTarget, CAMERA_ATTRACT_TRANS_SPEED) == true &&
				camera->TransitionPos(CAMERA_ATTRACT_POS, cPos, CAMERA_ATTRACT_TRANS_SPEED) == true)
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
			camera->FollowToPlayer(CAMERA_ATTRACT_TARGET_POS, CAMERA_ATTRACT_POS);
		}
	}
	else
	{
		if (isTraned == false)
		{
			//‘JˆÚ‚³‚¹‚é
			if (camera->TransitionPos(CAMERA_ATTRACT_TARGET_POS, cTarget, CAMERA_ATTRACT_ATTACK_TO_ATTRACT_TRANS_SPEED) == true &&
				camera->TransitionPos(CAMERA_ATTRACT_POS, cPos, CAMERA_ATTRACT_ATTACK_TO_ATTRACT_TRANS_SPEED) == true)
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
			camera->FollowToPlayer(CAMERA_ATTRACT_TARGET_POS, CAMERA_ATTRACT_POS);
		}
	}
}

void CameraState_Attract::End()
{
	isTraned = false;
}
