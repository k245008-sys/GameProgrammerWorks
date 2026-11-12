#include "Col_Slope.h"
#include"StageManager.h"
#include<assert.h>

Col_Slope::Col_Slope(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Col_Slope::Col_Slope(const VECTOR& _pos, const VECTOR& _rot, int _hModel) : Col_Slope(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Col_Slope::~Col_Slope()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Col_Slope::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);
}
