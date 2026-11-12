#include "F_Hill.h"
#include"StageManager.h"
#include<assert.h>

F_Hill::F_Hill(const VECTOR& _pos)
{
	hModel = MV1LoadModel("data/model/StageObjects/Hell/hall_gate.mv1");
	assert(hModel >= 0);

	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

F_Hill::F_Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :F_Hill(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

F_Hill::~F_Hill()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void F_Hill::Draw()
{
	Object3D::Draw();
}
