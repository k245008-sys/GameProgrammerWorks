#pragma once
#include "../Library/myDxLib.h"
#include "../Library/Time.h"

class SnapMove
{
public:
	SnapMove() : distance(VZero), judgeNearDist(0), speed(0), addSpeed(0),
	isFirstUnion(false) {}

	VECTOR CalcVelocity(const float& _addSpeedValue,
		const float& _speedMax, const float& _nearSpeed);
	VECTOR CalcVelocity(float& _speed, const float& _addSpeedValue,
		const float& _speedMax, const float& _nearSpeed);
	void SetJudgeNearDist(const float& _finishDistAlreadyNear,
		const float& _nearFinishDist, const float& _nearDistRateAlreadyNear);
	bool JudgeFinishAndGetFinishVel(VECTOR& _setVel,
		const VECTOR& _velrPos, const VECTOR& _velrVel,
		const VECTOR& _targetPos, const float& _judgeFinishDist);

	void ResetFirstUnion() { isFirstUnion = false; }

	void Reset()
	{
		distance = VZero;
		judgeNearDist = 0;
		speed = 0;
		addSpeed = 0;
		isFirstUnion = false;
	}

	void PlaySound_velFirst();

	VECTOR GetDistance() { return distance; }
	void SetDistance(const VECTOR& _distance) { distance = _distance; }

private:
	void PlaySound_Union();

	VECTOR distance;
	float judgeNearDist;
	float speed;
	float addSpeed;
	bool isFirstUnion;
};