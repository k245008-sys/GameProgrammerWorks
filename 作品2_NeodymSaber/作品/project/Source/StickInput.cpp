#include "StickInput.h"

namespace
{
	// スティック傾き率の最低値
	const float STICK_TILT_RATE_MIN = 0.001f;
}

StickInput::StickInput()
{
	AddInfo("L");
	AddInfo("R");
}

StickInput::~StickInput()
{
	infos.clear();
}

void StickInput::Update()
{
	// 左スティック入力位置
	StickInputInfo& left = infos["L"];
	GetJoypadAnalogInput(&left.pos.x, &left.pos.y, ctrlNo);
	// 右スティック入力位置
	StickInputInfo& right = infos["R"];
	GetJoypadAnalogInputRight(&right.pos.x, &right.pos.y, ctrlNo);

	for (auto& info : infos)
	{
		StickInputInfo& sInfo = info.second;
		// 入力があったか
		sInfo.isInput.last = sInfo.isInput.current;
		sInfo.isInput.current = (sInfo.pos.x != 0 || sInfo.pos.y != 0);

		// 入力方向
		sInfo.angle = atan2f((float)sInfo.pos.y, (float)sInfo.pos.x);
		// 上方向が０度になるよう調整する
		float adjust = (sInfo.isInput.current) ? DEGREE * 90 : 0;
		sInfo.angle += adjust;
		// 管理しやすいよう、右半分１８０度、左半分－１８０度にする
		if (sInfo.angle > DEGREE * 180)
			sInfo.angle -= DEGREE * 360;
		if (sInfo.angle < DEGREE * -180)
			sInfo.angle += DEGREE * 360;

		// 端までどれくらい傾けられたかの割合
		float tilt = (float)abs(sInfo.pos.x) + abs(sInfo.pos.y);
		sInfo.tiltRate = tilt / STICK_INPUT_MAX;
		if (sInfo.isInput.current && sInfo.tiltRate < STICK_TILT_RATE_MIN)
			sInfo.tiltRate = STICK_TILT_RATE_MIN;
	}
}