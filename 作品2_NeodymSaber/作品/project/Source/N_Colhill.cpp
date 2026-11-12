#include "N_Colhill.h"
#include"StageManager.h"
#include<assert.h>

N_Colhill::N_Colhill(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

N_Colhill::N_Colhill(const VECTOR& _pos, const VECTOR& _rot, int _hModel):N_Colhill(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

N_Colhill::~N_Colhill()
{
	MV1DeleteModel(hModel);
}

void N_Colhill::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);
}
