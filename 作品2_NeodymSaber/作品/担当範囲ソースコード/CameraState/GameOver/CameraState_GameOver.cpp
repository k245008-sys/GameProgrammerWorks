#include "CameraState_GameOver.h"
#include "Camera.h"
#include "Player.h"

void CameraState_GameOver::Update()
{
	VECTOR cTarget = camera->GetNormalTarget();
	VECTOR cPos = camera->GetPos();

	//判定を切る。
	camera->SetIsCollision(false);

	if (isTraned == false)
	{
		//遷移させる
		if (camera->TransitionPos(CAMERA_GAMEOVER_TARGET_POS, cTarget, CAMERA_GAMEOVER_TARGET_TRANS_SPEED) == true &&
			camera->TransitionPos(CAMERA_GAMEOVER_POS, cPos, CAMERA_GAMEOVER_POS_TRANS_SPEED) == true)
		{
			isTraned = true;
		}

		//位置と注視点をセット
		camera->SetNormalTarget(cTarget);
		camera->SetPos(cPos);
	}
	else
	{
		//遷移が終わったら追従
		camera->FollowToPlayer(CAMERA_GAMEOVER_TARGET_POS, CAMERA_GAMEOVER_POS);
	}
}

void CameraState_GameOver::End()
{
	isTraned = false;
}
