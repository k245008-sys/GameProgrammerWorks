#pragma once
#include "CameraStateBase.h"

class CameraState_Nomal : public CameraStateBase
{
public:

	CameraState_Nomal();
	~CameraState_Nomal() {};
	void Update() override;
	void End() override;

	void AssignFindObjToField() override;
};

