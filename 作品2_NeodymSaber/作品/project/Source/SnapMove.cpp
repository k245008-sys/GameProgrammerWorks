#include "SnapMove.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "SoundValue.h"
#include "EffectValue.h"
#include "CharaValue.h"
#include "InputManager.h"
#include "VibrationValue.h"

VECTOR SnapMove::CalcVelocity(const float& _addSpeedValue, const float& _speedMax, const float& _nearSpeed)
{
	if (VSize(distance) < judgeNearDist)
	{
		speed = _nearSpeed;
	}
	else
	{
		addSpeed += _addSpeedValue;
		speed += addSpeed;
		if (speed > _speedMax)
			speed = _speedMax;
	}
	return VNorm(distance) * speed;
}

VECTOR SnapMove::CalcVelocity(float& _speed, const float& _addSpeedValue, const float& _speedMax, const float& _nearSpeed)
{
	if (VSize(distance) < judgeNearDist)
	{
		speed = _nearSpeed;
	}
	else
	{
		addSpeed += _addSpeedValue;
		speed += addSpeed;
		if (speed > _speedMax)
			speed = _speedMax;
	}
	_speed = speed;
	return VNorm(distance) * speed;
}

void SnapMove::SetJudgeNearDist(const float& _finishDistAlreadyNear, const float& _nearFinishDist, const float& _nearDistRateAlreadyNear)
{
	if (VSize(distance) < _finishDistAlreadyNear)
		judgeNearDist = _nearFinishDist;
	else if (VSize(distance) < _nearFinishDist)
		judgeNearDist = VSize(distance) * _nearDistRateAlreadyNear;
	else
		judgeNearDist = _nearFinishDist;
}

bool SnapMove::JudgeFinishAndGetFinishVel(VECTOR& _setVel, const VECTOR& _velrPos, const VECTOR& _velrVel, const VECTOR& _targetPos, const float& _judgeFinishDist)
{
	VECTOR moveVel = _velrVel * Time::GameDeltaTime();
	VECTOR movePos = _velrPos + moveVel;
	if (VSize(moveVel) >= VSize(distance) ||
		VSize(_targetPos - movePos) <= _judgeFinishDist)
	{
		_setVel = distance - VNorm(distance) * _judgeFinishDist;
		_setVel /= Time::GameDeltaTime();
		if (!isFirstUnion)
		{
			InputManager* input = SceneManager::CommonScene()->FindGameObject<InputManager>();
			if (input->GetEnableVib())
				StartJoypadVibration(DX_INPUT_PAD1, VIBRATION_POWER_SNAP_UNION, VIBRATION_TIME_SNAP_UNION);
			PlaySound_Union();
		}
		isFirstUnion = true;
		return true;
	}
	return false;
}

void SnapMove::PlaySound_velFirst()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Play("SnapAttract");
}

void SnapMove::PlaySound_Union()
{
	SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
	sound->Play("SnapUnion1");
}
