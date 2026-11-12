#pragma once
#include "Object3D.h"
#include "../Library/Time.h"

class Shot_Straight : public Object3D
{
public:
	Shot_Straight();
	~Shot_Straight();
	virtual void Update()override;
	virtual void Draw()override;

	bool GetEnable() { return enable; }
	VECTOR GetVelocity() { return velocity; }
	VECTOR GetVelocityGameDelta() { return velocity * Time::GameDeltaTime(); }
	float GetElapsedTime() { return elapsedTime; }

	void EnableOn(const VECTOR& _pos, const VECTOR& _rot, const float& _speed);
	void EnableOff();

private:
	bool enable;
	VECTOR velocity;
	float elapsedTime;
	float speed;
};