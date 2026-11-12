#pragma once

namespace Util
{
	// 角度を-180度～180度に正規化(ラジアン)
	inline void NormalizeAngle(float& _angle)
	{
		while (_angle > DEGREE * 180)
			_angle -= DEGREE * 360;
		while (_angle < DEGREE * -180)
			_angle += DEGREE * 360;
	}

	// クランプ(範囲制限)関数
	template <typename T>
	inline void Clamp(T& _clampNum, const T& _min, const T& _max)
	{
		if (_clampNum < _min)
			_clampNum = _min;
		if (_clampNum > _max)
			_clampNum = _max;
	}
	inline void ClampNorm(VECTOR& _norm)
	{
		Clamp<float>(_norm.x, -1, 1);
		Clamp<float>(_norm.y, -1, 1);
		Clamp<float>(_norm.z, -1, 1);
	}

	// 符号取得
	template <typename T>
	inline int GetSign(const T& _num)
	{
		if (_num < 0)
			return -1;
		else
			return 1;
	}

	/// <summary>
	/// float型の乱数取得
	/// </summary>
	/// <param name="_min">最小値</param>
	/// <param name="_max">最大値</param>
	/// <param name="_decimalPlace">小数第何位まで有効にするか</param>
	/// <returns>乱数結果</returns>
	inline float GetRandF(const float& _min, const float& _max, const int& _decimalPlace = 1)
	{
		int dig = 1;
		int count = _decimalPlace;
		while (count > 0)
		{
			dig *= 10;
			count--;
		}
		int min = (int)(_min * dig);
		int max = (int)(_max * dig);
		float result = min + (float)GetRand((max - min) + 1) - 1;
		result /= dig;
		return result;
	}

	// VECTOR型の乱数取得
	inline VECTOR GetRandV(const VECTOR& _min, const VECTOR& _max, const int& _decimalPlace = 1)
	{
		VECTOR result = VZero;
		result.x = GetRandF(_min.x, _max.x, _decimalPlace);
		result.y = GetRandF(_min.y, _max.y, _decimalPlace);
		result.z = GetRandF(_min.z, _max.z, _decimalPlace);
		return result;
	}

	template <typename T>
	inline void SetSignRand(T& _num)
	{
		int sign = (bool)GetRand(1) ? 1 : -1;
		_num *= sign;
	}

	inline void SetSignRandV(VECTOR& _num)
	{
		SetSignRand<float>(_num.x);
		SetSignRand<float>(_num.y);
		SetSignRand<float>(_num.z);
	}
}