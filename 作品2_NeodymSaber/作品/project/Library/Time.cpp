#include "Time.h"
#include <Windows.h>

namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float realDeltaTime;
	float gameDeltaTime;
};

void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);
}

void Time::RefreshRealDeltaTime()
{
	// 前回のフレームから現実で何秒経過したかを取得
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	realDeltaTime = static_cast<float>(current.QuadPart - last.QuadPart) / freq.QuadPart;
}

float Time::RealDeltaTime()
{
	return realDeltaTime;
}

void Time::SetGameDeltaTime(const float& _gameDeltaTime)
{
	gameDeltaTime = _gameDeltaTime;
}

float Time::GameDeltaTime()
{
	return gameDeltaTime;
}
