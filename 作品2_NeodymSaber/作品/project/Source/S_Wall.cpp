#include "S_Wall.h"
#include "StageManager.h"
#include <assert.h>

S_Wall::S_Wall(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

S_Wall::S_Wall(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :S_Wall(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

S_Wall::~S_Wall()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void S_Wall::Draw()
{
	Object3D::Draw();
}