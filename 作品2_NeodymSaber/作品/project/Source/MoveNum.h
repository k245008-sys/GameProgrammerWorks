#pragma once
#include "../Library/myDxLib.h"

/*
	ある値を指定速度で目標まで動かす機能まとめ
	綾部
*/

class MoveNum
{
public:
	/// <summary>
	/// 値を目標まで移動する
	/// </summary>
	/// <param name="_num">動かす値</param>
	/// <param name="_vel">速度</param>
	/// <param name="_limit">目標値</param>
	/// <returns>目標値に達したか</returns>
	template <typename T>
	bool MoveToTarget(T& _num, const T& _vel, const T& _limit)
	{
		if (_num == _limit)
		{
			return true;
		}
		// 目標より大きければ引く
		else if (_num > _limit)
		{
			_num -= fabsf(_vel);
			if (_num <= _limit)
			{
				_num = _limit;
				return true;
			}
		}
		// 目標より小さければ足す
		else
		{
			_num += fabsf(_vel);
			if (_num >= _limit)
			{
				_num = _limit;
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// 値を目標まで動かす(VECTOR)
	/// </summary>
	/// <param name="_v">動かす値</param>
	/// <param name="_vel">軸ごとの速度</param>
	/// <param name="_target">目標値</param>
	/// <returns>目標に達したか</returns>
	bool MoveToTargetV(VECTOR& _v, const VECTOR& _vel, const VECTOR& _target);

	/// <summary>
	/// 値を目標まで加算
	/// </summary>
	/// <param name="_num">動かす値</param>
	/// <param name="_vel">加算する速度</param>
	/// <param name="_limit">目標値</param>
	/// <returns>目標に達したか</returns>
	template <typename T>
	bool AddToTarget(T& _num, const T& _vel, const T& _limit)
	{
		if (_num == _limit)
			return true;
		// 目標より小さければ足す
		if (_num < _limit)
		{
			_num += fabsf(_vel);
			if (_num >= _limit)
			{
				_num = _limit;
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// 値を目標まで減算
	/// </summary>
	/// <param name="_num">動かす値</param>
	/// <param name="_vel">減算する速度</param>
	/// <param name="_limit">目標値</param>
	/// <returns>目標に達したか</returns>
	template <typename T>
	bool SubToTarget(T& _num, const T& _vel, const T& _limit)
	{
		if (_num == _limit)
			return true;
		// 目標より大きければ引く
		if (_num > _limit)
		{
			_num -= fabsf(_vel);
			if (_num <= _limit)
			{
				_num = _limit;
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// 値を目標まで３次元ベクトル(速度指定)で動かす
	/// </summary>
	/// <param name="_v">動かす値</param>
	/// <param name="_vel">ベクトルの速度</param>
	/// <param name="_target">目標値</param>
	/// <returns>目標に達したか</returns>
	bool MoveVector(VECTOR& _v, const float& _vel, const VECTOR& _target);

	/// <summary>
	/// 回転値の移動
	/// </summary>
	/// <param name="_rot">回転させる値</param>
	/// <param name="_vel">回転させる速度</param>
	/// <param name="_target">目標値</param>
	/// <returns>目標に達したか</returns>
	bool MoveRot(float& _rot, const float& _vel, const float& _target);
};
