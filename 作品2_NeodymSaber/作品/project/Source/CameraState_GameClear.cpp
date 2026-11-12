#include "CameraState_GameClear.h"
#include "CameraAdjustValue.h"
#include "Camera.h"
#include "Player.h"

CameraState_GameClear::CameraState_GameClear()
{
	Pos = VGet(0.0f, 0.0f, 0.0f);
	GoalPos = VGet(0.0f, 0.0f, 0.0f);
	RotY = 0.0f;
	cRotY = 0.0f;
	counter = 0.0f;
	isResetAngle = false;
	isDown = false;
	isUp = false;
}

void CameraState_GameClear::Update()
{
	if (isResetAngle == false)
	{
		//指定の場所にカメラを設置し遷移させる。
		isResetAngle = true;
		camera->SetRot(player->GetRot());
		cRotY = camera->GetRot().y;
		RotY = camera->GetRot().y;
		GoalPos = VGet(52.0f, 284.0f, -301.0f);
		camera->SetCenterToPlayer(CAMERA_GAMECLEAR_TARGET_POS, GoalPos, camera->GetRot());
		isDown = true;
	}

	//回転ーーーーーーーーー

	if (RotY >  cRotY + CAMERA_GAMECLEAR_FIRST_ROT)
	{
		RotY -= CAMERA_GAMECLEAR_ROT_SPEED * DEGREE;
	}
	camera->SetRot(VGet(camera->GetRot().x, RotY, camera->GetRot().z));

	//ーーーーーーーーーー

	//移動ーーーーーーーーー

	//Y軸
	if (isDown == true)
	{
		if (GoalPos.y > CAMERA_GAMECLEAR_UNDER_MAX)
		{
			GoalPos.y -= CAMERA_GAMECLEAR_DOWN_SPEED;
		}
	}

	if (GoalPos.y < CAMERA_GAMECLEAR_UNDER_MAX)
	{
		isDown = false;
		isUp = true;
	}
	
	if (isUp == true)
	{
		if (GoalPos.y < CAMERA_GAMECLEAR_HIGHTER_MAX)
		{
			GoalPos.y += CAMERA_GAMECLEAR_UP_SPEED;
		}
	}
	
	//追従
	camera->FollowToPlayer(CAMERA_GAMECLEAR_TARGET_POS, GoalPos);
}

void CameraState_GameClear::End()
{
	isResetAngle = false;
	isDown = false;
	isUp = false;
}
