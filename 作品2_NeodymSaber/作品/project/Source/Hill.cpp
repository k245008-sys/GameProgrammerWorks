#include "Hill.h"
#include"StageManager.h"
#include<assert.h>

Hill::Hill(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Hill::Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Hill(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Hill::~Hill()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Hill::Draw()
{
	Object3D::Draw();
}