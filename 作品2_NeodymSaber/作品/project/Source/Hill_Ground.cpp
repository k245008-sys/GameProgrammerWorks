#include "Hill_Ground.h"
#include "W_Col.h"
#include"StageManager.h"
#include<assert.h>

Hill_Ground::Hill_Ground(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Hill_Ground::Hill_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Hill_Ground(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Hill_Ground::~Hill_Ground()
{
	MV1DeleteModel(hModel);
}

void Hill_Ground::Draw()
{
	/*
	if (CheckHitKey(KEY_INPUT_5))
	{
		if (!push)
		{
			(coll) ? coll = false : coll = true;

			push = true;
		}
	}
	else
		push = false;
	if (coll)
	{
		Object3D::Draw();
	}
	else
	{
		MATRIX mat = GetDrawMatrix();
		MV1SetMatrix(hModel, mat);
	}
	*/
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);
}
