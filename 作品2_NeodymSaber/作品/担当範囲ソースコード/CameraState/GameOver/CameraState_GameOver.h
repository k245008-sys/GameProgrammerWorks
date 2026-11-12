#pragma once
#include "CameraStateBase.h"

class CameraState_GameOver : public CameraStateBase
{
public:

	CameraState_GameOver() {};
	~CameraState_GameOver() {};
	void Update() override;
	void End() override;
};
