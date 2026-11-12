#pragma once
#include "../Library/myDxLib.h"
#include <math.h>

template<typename T>
inline T Lerp(T _begin, T _end, float _rate)
{
	return (_end - _begin) * _rate + _begin;
}

// Å‰‚ª‘‚­AI‚í‚èÛ‚ä‚Á‚­‚è‚É‚È‚é
inline float EaseOutQuint(const float& _in)
{
	float in = _in;
	if (in > 1.0f)
		in = 1.0f;
	return 1 - powf(1 - in, 5);
}

// Å‰­‚µ‚¾‚¯‚ä‚Á‚­‚èA‚·‚®‘‚­‚È‚é
inline float EaseInQuint(const float& _in)
{
	float in = _in;
	if (in > 1.0f)
		in = 1.0f;
	return in * in * in * in * in;
}