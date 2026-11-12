#include "DrawBox3D.h"
#include "../Library/myDxLib.h"

void DrawBox3D::DrawFront(const VECTOR& _pos, const VECTOR& _size, const VECTOR& _rot, const unsigned int& _color, const int& _alpha)
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);

	MATRIX mRot = MGetRotZXY(_rot);
	VECTOR maxPos = _size;
	VECTOR minPos = VGet(-_size.x, 0, 0);

	VECTOR lUpFront = _pos + VGet(minPos.x, maxPos.y, maxPos.z) * mRot;
	VECTOR lDownFront = _pos + VGet(minPos.x, minPos.y, maxPos.z) * mRot;
	VECTOR rUpFront = _pos + maxPos * mRot;
	VECTOR rDownFront = _pos + VGet(maxPos.x, minPos.y, maxPos.z) * mRot;
	VECTOR lUpBack = _pos + VGet(minPos.x, maxPos.y, minPos.z) * mRot;
	VECTOR lDownBack = _pos + minPos * mRot;
	VECTOR rUpBack = _pos + VGet(maxPos.x, maxPos.y, minPos.z) * mRot;
	VECTOR rDownBack = _pos + VGet(maxPos.x, minPos.y, minPos.z) * mRot;

	int f = TRUE;
	DrawTriangle3D(lDownBack, lDownFront, lUpBack, _color, f);
	DrawTriangle3D(lDownFront, lUpFront, lUpBack, _color, f);
	DrawTriangle3D(rDownBack, rDownFront, rUpBack, _color, f);
	DrawTriangle3D(rDownFront, rUpFront, rUpBack, _color, f);

	DrawTriangle3D(lDownBack, rDownBack, lUpBack, _color, f);
	DrawTriangle3D(rDownBack, rUpBack, lUpBack, _color, f);
	DrawTriangle3D(lDownFront, rDownFront, lUpFront, _color, f);
	DrawTriangle3D(rDownFront, rUpFront, lUpFront, _color, f);

	DrawTriangle3D(lDownBack, lDownFront, rDownBack, _color, f);
	DrawTriangle3D(rDownBack, rDownFront, lDownFront, _color, f);
	DrawTriangle3D(lUpBack, lUpFront, rUpBack, _color, f);
	DrawTriangle3D(rUpBack, rUpFront, lUpFront, _color, f);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetWriteZBuffer3D(TRUE);
}
