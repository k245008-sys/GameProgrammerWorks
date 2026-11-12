#include "Slope_Col.h"
#include "W_Col.h"
#include"StageManager.h"
#include<assert.h>

Slope_Col::Slope_Col(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Slope_Col::Slope_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Slope_Col(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Slope_Col::~Slope_Col()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Slope_Col::Draw()
{		MATRIX mat = GetDrawMatrix();
		MV1SetMatrix(hModel, mat);
	
}
