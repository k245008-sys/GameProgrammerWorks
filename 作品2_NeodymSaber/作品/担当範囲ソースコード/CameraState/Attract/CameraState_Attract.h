#pragma once
#include "CameraStateBase.h"

class CameraState_Attract : public CameraStateBase
{
public:

	CameraState_Attract() {};
	~CameraState_Attract() {};
	void Update() override;
	void End() override;
};

