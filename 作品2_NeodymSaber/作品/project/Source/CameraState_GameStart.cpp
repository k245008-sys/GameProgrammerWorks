#include "CameraState_GameStart.h"
#include "Camera.h"
#include "Player.h"

CameraState_GameStart::CameraState_GameStart()
{
	isFirstPosSet = false;
}

void CameraState_GameStart::Update()
{
	if (isFirstPosSet == false)
	{
		//カメラの最初の位置をセット
		camera->SetCenterToPlayer(VGet(0.0f, 100.0f, 0.0f), VGet(0.0f, 50.0f, -200.0f), VGet(0.0f, 0.0f * DEGREE, 0.0f));
		isFirstPosSet = true;
	}

	if (isFirstPosSet == true && isTraned == false)
	{
		VECTOR cTarget = camera->GetNormalTarget();
		VECTOR cPos = camera->GetPos();

		//遷移の開始、どこまでカメラを動かすか。
		if (camera->TransitionPos(CAMERA_DEF_TARGET_POS, cTarget, 18.5f) == true &&
			camera->TransitionPos(CAMERA_DEF_POS, cPos, 18.5f) == true)
		{
			isTraned = true;
		}

		//動かした位置と注視点をカメラにセット
		camera->SetNormalTarget(cTarget);
		camera->SetPos(cPos);
	}
	else
	{
		//遷移終了後の処理
		camera->FollowToPlayer(CAMERA_DEF_TARGET_POS, CAMERA_DEF_POS);
		nextStateName = "Normal";
	}
}

void CameraState_GameStart::End()
{
	camera->FollowToPlayer(CAMERA_DEF_TARGET_POS, CAMERA_DEF_POS);
	isFirstPosSet = false;
	isTraned = false;
}
