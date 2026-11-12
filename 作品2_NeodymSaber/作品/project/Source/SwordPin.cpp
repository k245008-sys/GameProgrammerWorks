#include "SwordPin.h"
#include"ColorValue.h"
#include"UiValue.h"
#include<assert.h>
#include "debugScreen.h"
#include"Camera.h"
#include"Player.h"
#include"Sword_Throw.h"
#include "config.h"
#include <iostream>
#include <algorithm>
#include "Util.h"

SwordPin::SwordPin()
{
	camera = nullptr;
	sword = nullptr;
	swordImage = -1;
	extRate = 0.0f;
	flameAngle = 0.0f;
	isAppear = false;
	redSword = 0.0f;
	alpha_num = 0;
}

SwordPin::SwordPin(VECTOR2I Pos, int image, int flameimage) : SwordPin()
{
	swordImage = LoadGraph("data/texture/Red_ken-1.png");
	assert(swordImage >= 0);

	hImage = image;
	Flameimage = flameimage;
	pos = Pos;
}

SwordPin::~SwordPin()
{
	DeleteGraph(swordImage);
}

void SwordPin::Update()
{
	using namespace Util;

	Player* player = FindGameObject<Player>();
	Sword_Throw* sw_throw = player->GetSword_Throw();
	VECTOR swPos = sw_throw->GetPos();

	// 表示条件
	isAppear = sw_throw->GetCurrentStateName() == "Pierced" && CheckCameraViewClip(swPos);

	if (isAppear)
	{

		// ワールド座標をスクリーン座標に変換
		VECTOR conv = ConvWorldPosToScreenPos(swPos);
		pos.x = (int)conv.x;
		pos.y = (int)conv.y;

		// 剣が手前にある時、スクリーン座標が反転してしまうので補正する
		VECTOR2I screenCenter = VECTOR2I(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		VECTOR2I distance = pos - screenCenter;
		float diffAngle = atan2f((float)distance.y, (float)distance.x);
		int adjust = 200;
		pos.x = screenCenter.x + (int)((screenCenter.x + adjust) * cosf(diffAngle));
		pos.y = screenCenter.y + (int)((screenCenter.y + adjust) * sinf(diffAngle));
		distance = pos - screenCenter;

		if (conv.z > 1)	// Zが１以上の時＝剣が手前にある時
		{

			// 画面中心からの長さを逆にすることで反転
			pos.x = screenCenter.x - distance.x;
			pos.y = screenCenter.y - distance.y;
		}

		// 表示位置の範囲制限
		VECTOR2I clampSize;
		GetGraphSize(hImage, &clampSize.x, &clampSize.y);

		clampSize /= 2;

		clampSize += SWORD_PIN_ADJUST_CLAPM_SIZE;
		Clamp(pos.x, clampSize.x, SCREEN_WIDTH - clampSize.x);
		Clamp(pos.y, clampSize.y, SCREEN_HEIGHT - clampSize.y);

		// 剣のある方向へ向かせる
		distance = pos - screenCenter;
		flameAngle = atan2f((float)distance.y, (float)distance.x);

		extRate = 1;
	}
	else if (sw_throw->GetCurrentStateName() == "Pierced")
	{
		VECTOR conv = ConvWorldPosToScreenPos(swPos);
		gaugePos.x = (int)conv.x;
		gaugePos.y = (int)conv.y;
		flameAngle = 0;
	}

	if (sw_throw->GetCurrentStateName() == "Pierced")
	{
		VECTOR P_SW = player->GetPos() - swPos;

		/*
		if (P_SW.x > 700 || P_SW.z > 700 || P_SW.y > 700)
		{
			alpha_num++;
		}
		else
			alpha_num -= 2;

		if (alpha_num > SWORD_PIN_ALHPA_MAX)
		{
			alpha_num = SWORD_PIN_ALHPA_MAX;
		}

		if (alpha_num < SWORD_PIN_ALHPA_MIN)
		{
			alpha_num = SWORD_PIN_ALHPA_MIN;
		}
		*/
	}

}

void SwordPin::Draw()
{

	if (isAppear)
	{
		DrawRotaGraph3(pos.x, pos.y, (int)SWORD_PIN_CENTER_RETE, (int)SWORD_PIN_CENTER_RETE, extRate, extRate, SWORD_PIN_ADJUST_ANGLE + flameAngle, Flameimage, true, false);
		DrawRectGraph((int)pos.x - SWORD_PIN_POS_SHIFTX, (int)pos.y - SWORD_PIN_POS_SHIFTY, 0, 0, SWORD_FOTE_SIZE, SWORD_FOTE_SIZE, swordImage, true, false);
	}
}