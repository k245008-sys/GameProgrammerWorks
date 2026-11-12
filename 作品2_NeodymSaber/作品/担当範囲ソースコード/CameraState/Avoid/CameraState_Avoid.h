#pragma once
#include "CameraStateBase.h"

class CameraState_Avoid : public CameraStateBase
{
public:

	CameraState_Avoid() {};
	~CameraState_Avoid() {};
	void Update() override;
	void End() override {};
};