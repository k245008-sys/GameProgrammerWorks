#pragma once
#include "CameraStateBase.h"

class CameraState_Snap : public CameraStateBase
{
public:

	CameraState_Snap() {};
	~CameraState_Snap(){};
	void Update() override;
	void End() override;
};

