#pragma once
#include "SwordValue.h"
#include "../Library/myDxLib.h"

class CommonFunc_CollDraw
{
public:
	void AttractRange_Red(const VECTOR& _pos)
	{
		SetWriteZBuffer3D(FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SWORD_PIERCED_ATTRACT_DIST_DRAW_ALPHA);
		DrawSphere3D(_pos, SWORD_PIERCED_ATTRACT_DIST,
			SWORD_PIERCED_ATTRACT_DIST_DRAW_DIV_NUM,
			SWORD_PIERCED_ATTRACT_DIST_DRAW_DIF_COLOR,
			SWORD_PIERCED_ATTRACT_DIST_DRAW_SPC_COLOR,
			(int)SWORD_PIERCED_ATTRACT_DIST_DRAW_FILL);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetWriteZBuffer3D(TRUE);
	}

	void DrawCapsule(const VECTOR& _root, const VECTOR& _tip, const float& _rad, const unsigned int& _color, const float& _alphaPercent)
	{
		unsigned int alpha = (int)(255 * (_alphaPercent / 100));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawCapsule3D(_root, _tip, _rad, 16, _color, _color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};