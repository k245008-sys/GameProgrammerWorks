#include "High_Col.h"
#include "StageManager.h"
#include <assert.h>

High_Col::High_Col(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_COLLSION_HIGE_SCALE;

	push = false;
	coll = false;
}

High_Col::High_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel):High_Col(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

High_Col::~High_Col()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void High_Col::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);

}
