#pragma once
#include "CameraStateBase.h"

class CameraState_GameClear : public CameraStateBase
{
public:

	CameraState_GameClear();
	~CameraState_GameClear() {};
	void Update() override;
	void End() override;

private:

	VECTOR Pos;
	VECTOR GoalPos;
	float RotY;
	float cRotY;
	float counter;

	bool isResetAngle;
	bool isDown;
	bool isUp;
};
