#include "N_Hill.h"
#include"StageManager.h"
#include<assert.h>


N_Hill::N_Hill(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

N_Hill::N_Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :N_Hill(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

N_Hill::~N_Hill()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void N_Hill::Draw()
{
	Object3D::Draw();
}
