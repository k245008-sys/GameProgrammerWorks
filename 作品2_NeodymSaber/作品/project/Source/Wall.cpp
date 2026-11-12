#include "Wall.h"
#include <assert.h>

Wall::Wall(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Wall::Wall(const VECTOR& _pos, const VECTOR& _rot, int _hModel):Wall(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Wall::Wall()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Wall::Draw()
{
	Object3D::Draw();
}
