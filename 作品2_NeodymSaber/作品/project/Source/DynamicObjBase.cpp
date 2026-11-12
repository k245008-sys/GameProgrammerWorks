#include "DynamicObjBase.h"

DynamicObjBase::DynamicObjBase()
{
	stateManager = nullptr;
	velocity = VZero;
}

DynamicObjBase::~DynamicObjBase()
{
	if (stateManager != nullptr)
	{
		delete stateManager;
		stateManager = nullptr;
	}
}

void DynamicObjBase::Update()
{
	stateManager->SetParentToCurrentState(this);
	stateManager->AssignFindObjToFieldAll();
	if (stateManager != nullptr)
		stateManager->Update();
}

void DynamicObjBase::Draw()
{
	Object3D::Draw();
	stateManager->SetParentToCurrentState(this);
	if (stateManager != nullptr)
		stateManager->Draw();
}

void DynamicObjBase::ChangeStateOnce(const std::string& _stateName)
{
	stateManager->SetParentToCurrentState(this);
	stateManager->ChangeCurrentStateOnce(_stateName);
}

void DynamicObjBase::ChangeState(const std::string& _stateName)
{
	stateManager->SetParentToCurrentState(this);
	stateManager->ChangeCurrentState(_stateName);
}
