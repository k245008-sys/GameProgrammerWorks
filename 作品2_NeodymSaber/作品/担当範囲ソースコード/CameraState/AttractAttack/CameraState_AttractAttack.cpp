#include "CameraState_AttractAttack.h"
#include "Camera.h"
#include "Player.h"

void CameraState_AttractAttack::Update()
{
	VECTOR cTarget = camera->GetNormalTarget();
	VECTOR cPos = camera->GetPos();
	
	if (isTraned == false)
	{
		//遷移させる
		if(camera->TransitionPos(CAMERA_ATTRACT_TARGET_POS, cTarget, CAMERA_ATTRACT_ATTACK_TARGET_POS_TRANS_SPEED) == true &&
			camera->TransitionPos(CAMERA_ATTRACT_ATTACK_POS, cPos, CAMERA_ATTRACT_ATTACK_POS_TRANS_SPEED) == true)
		{
			
			isTraned = true;
		}

		//位置と注視点をセット
		camera->SetNormalTarget(cTarget);
		camera->SetPos(cPos);

	}
	else
	{
		//追従
		camera->FollowToPlayer(CAMERA_ATTRACT_ATTACK_TARGET_POS, CAMERA_ATTRACT_ATTACK_POS);
	}
	
}

void CameraState_AttractAttack::End()
{
	isTraned = false;
}
