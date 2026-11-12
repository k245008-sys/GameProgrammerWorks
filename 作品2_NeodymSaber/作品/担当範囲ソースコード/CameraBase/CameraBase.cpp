#include "CameraBase.h"

CameraBase::CameraBase()
{
	stateManager = nullptr;
}

void CameraBase::Update()
{
	if (stateManager != nullptr)
	{
		//ステートで使うポインターを更新する。
		stateManager->AssignFindObjToFieldAll();
		stateManager->Update();
	}
}

void CameraBase::Draw()
{
	if (stateManager != nullptr)
	{
		stateManager->Draw();
	}
}


