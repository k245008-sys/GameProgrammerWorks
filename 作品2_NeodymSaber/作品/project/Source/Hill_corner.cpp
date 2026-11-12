#include "Hill_corner.h"
#include"StageManager.h"
#include<assert.h>

Hill_corner::Hill_corner(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Hill_corner::Hill_corner(const VECTOR& _pos, const VECTOR& _rot, int _hModel):Hill_corner(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Hill_corner::~Hill_corner()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Hill_corner::Draw()
{
	Object3D::Draw();
}
