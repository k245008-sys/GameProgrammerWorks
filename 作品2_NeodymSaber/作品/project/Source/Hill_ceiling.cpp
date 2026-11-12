#include "Hill_ceiling.h"
#include"StageManager.h"
#include<assert.h>

Hill_ceiling::Hill_ceiling(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Hill_ceiling::Hill_ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Hill_ceiling(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Hill_ceiling::~Hill_ceiling()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Hill_ceiling::Draw()
{
	Object3D::Draw();
}
