#pragma once
#include "CameraStateBase.h"

class CameraState_AttractAttack : public CameraStateBase
{
public:

	CameraState_AttractAttack() {};
	~CameraState_AttractAttack() {};
	void Update() override;
	void End() override;
};

