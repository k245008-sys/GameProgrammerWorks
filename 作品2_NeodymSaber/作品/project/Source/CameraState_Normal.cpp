#include "CameraState_Normal.h"
#include "CameraAdjustValue.h"
#include "Camera.h"
#include "Player.h"
#include "Camera.h"

CameraState_Nomal::CameraState_Nomal()
{
	AssignFindObjToField();
}

void CameraState_Nomal::Update()
{
	VECTOR cPos = camera->GetPos();
	VECTOR cTarget = camera->GetNormalTarget();

	if (isTraned == false)
	{
		//‘JˆÚ‚³‚¹‚é
		if (camera->TransitionPos(CAMERA_DEF_TARGET_POS, cTarget, CAMERA_DEF_TRANS_SPEED) == true &&
			camera->TransitionPos(CAMERA_DEF_POS, cPos, CAMERA_DEF_TRANS_SPEED) == true)
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
		camera->FollowToPlayer(CAMERA_DEF_TARGET_POS, CAMERA_DEF_POS);
	}
}

void CameraState_Nomal::End()
{
	isTraned = false;
}

void CameraState_Nomal::AssignFindObjToField()
{
	CameraStateBase::AssignFindObjToField();
}
