#include "MoveNum.h"
#include "../Library/Time.h"
#include "Util.h"

bool MoveNum::MoveToTargetV(VECTOR& _v, const VECTOR& _vel, const VECTOR& _target)
{
	// ３軸全てが目標値に達したか
	bool x = MoveToTarget(_v.x, _vel.x, _target.x);
	bool y = MoveToTarget(_v.y, _vel.y, _target.y);
	bool z = MoveToTarget(_v.z, _vel.z, _target.z);
	return (x && y && z);
}

bool MoveNum::MoveVector(VECTOR& _v, const float& _vel, const VECTOR& _target)
{
	// 目標までのベクトル
	VECTOR dist = _target - _v;
	// 既に目標へ達していたら終了
	if (VSize(dist) == 0)
		return true;
	// 目標への移動ベクトル
	VECTOR move = VNorm(dist) * _vel;
	// 移動速度が目標との距離を上回っていたら
	if (VSize(move) > VSize(dist))
	{
		// 移動速度を距離にしてぴったり合わせる
		move = VNorm(move) * VSize(dist);
		_v += move;
		return true;
	}
	_v += move;
	return false;
}

bool MoveNum::MoveRot(float& _rot, const float& _vel, const float& _target)
{
	using namespace Util;

	// 角度を正規化
	float target = _target;
	NormalizeAngle(target);
	NormalizeAngle(_rot);
	// 角度差
	float diff = target - _rot;
	// 目標まで180度以上の差があるか
	bool over = (fabsf(diff) > DEGREE * 180);
	if (!over) // 差が180度以下なら
	{
		// そのまま目標に近づけて終了
		MoveNum move;
		move.MoveToTarget(_rot, _vel * Time::GameDeltaTime(), target);
		return true;
	}

	// 差が180度以上で正だったら
	if (GetSign(diff) == 1)
	{
		// 反対向きに近づける
		_rot -= _vel * Time::GameDeltaTime();
		// 現在値が180度を超えたら
		if (_rot < DEGREE * -180)
		{
			NormalizeAngle(_rot); // 正規化
			// 目標に達したか
			if (_rot < target)
			{
				_rot = target;
				return true;
			}
		}
	}
	// 差が180度以上で負だったら
	if (GetSign(diff) == -1)
	{
		// 反対向きに近づける
		_rot += _vel * Time::GameDeltaTime();
		if (_rot > DEGREE * 180)
		{
			NormalizeAngle(_rot); // 正規化
			// 目標に達したか
			if (_rot > target)
			{
				_rot = target;
				return true;
			}
		}
	}
	return false;
}