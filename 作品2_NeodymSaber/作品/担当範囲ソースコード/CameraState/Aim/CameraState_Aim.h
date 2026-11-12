#pragma once
#include "CameraStateBase.h"

class CameraState_Aim : public CameraStateBase
{
public:

	CameraState_Aim() {};
	~CameraState_Aim() {};
	void Update() override;
	void End() override;
};

