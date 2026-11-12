#pragma once
#include "CameraStateBase.h"
#include "Lerp.h"

class CameraState_GameStart : public CameraStateBase
{
public:

	CameraState_GameStart();
	~CameraState_GameStart() {};
	void Update() override;
	void End() override;

private:

	bool isFirstPosSet;
};
