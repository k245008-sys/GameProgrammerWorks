#pragma once
#include "CameraStateBase.h"

class CameraState_Attack : public CameraStateBase
{
public:

	CameraState_Attack() {};
	~CameraState_Attack() {};
	void Update() override;
	void End() override;
};