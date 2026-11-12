#include "G_Colhill.h"
#include"StageManager.h"
#include<assert.h>

G_Colhill::G_Colhill(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

G_Colhill::G_Colhill(const VECTOR& _pos, const VECTOR& _rot, int _hModel):G_Colhill(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

G_Colhill::~G_Colhill()
{
	MV1DeleteModel(hModel);
}

void G_Colhill::Draw()
{
	MATRIX mat = GetDrawMatrix();
	MV1SetMatrix(hModel, mat);
}
