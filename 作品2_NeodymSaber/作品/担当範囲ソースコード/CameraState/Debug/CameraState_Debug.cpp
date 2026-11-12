#include "CameraState_Debug.h"
#include "Camera.h"
#include "Player.h"
#include "InputManager.h"

CameraState_Debug::CameraState_Debug()
{
	position = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
}

void CameraState_Debug::Update()
{
	position = camera->GetPos();
	rotation = camera->GetRot();

	MoveCamera();
}

void CameraState_Debug::End()
{

}

void CameraState_Debug::MoveCamera()
{
	if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		position.z += cosf(camera->GetRot().y) * CAMERA_DEBUG_MOVE_SPEED;
		position.x += sinf(camera->GetRot().y) * CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}
	else if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		position.z -= cosf(camera->GetRot().y) * CAMERA_DEBUG_MOVE_SPEED;
		position.x -= sinf(camera->GetRot().y) * CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}

	if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		position.x += CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}

	else if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		position.x -= CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}

	if (CheckHitKey(KEY_INPUT_LSHIFT) != 0)
	{
		position.y -= CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}
	else if (CheckHitKey(KEY_INPUT_SPACE) != 0)
	{
		position.y += CAMERA_DEBUG_MOVE_SPEED;
		camera->SetPos(position);
	}


	if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		rotation.y -= CAMERA_ROTATION_SPEED_MAX.y;
		camera->SetRot(rotation);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		rotation.y += CAMERA_ROTATION_SPEED_MAX.y;
		camera->SetRot(rotation);
	}

	if (CheckHitKey(KEY_INPUT_UP) != 0)
	{
		rotation.x -= CAMERA_ROTATION_SPEED_MAX.x;
		camera->SetRot(rotation);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) != 0)
	{
		rotation.x += CAMERA_ROTATION_SPEED_MAX.x;
		camera->SetRot(rotation);
	}
	
	targetGoal = VTransform(VGet(0.0f, 0.0f, 100.0f), camera->GetDirection());
	targetGoal = VAdd(targetGoal, camera->GetPos());

	camera->SetNormalTarget(targetGoal);
}