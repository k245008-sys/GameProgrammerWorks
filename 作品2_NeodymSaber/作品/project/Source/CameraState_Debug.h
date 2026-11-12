#pragma once
#include "CameraStateBase.h"

class CameraState_Debug : public CameraStateBase
{
public:

	CameraState_Debug();
	~CameraState_Debug() {};
	void Update() override;
	void End() override;

	void MoveCamera();
	void DirectionCameraToMausePointer() {};

private:
	VECTOR position;
	VECTOR rotation;
	VECTOR targetGoal;
};

