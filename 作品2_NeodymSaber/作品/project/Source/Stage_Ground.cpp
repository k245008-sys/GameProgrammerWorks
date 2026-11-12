#include "Stage_Ground.h"
#include <assert.h>

Stage_Ground::Stage_Ground(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Stage_Ground::Stage_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Stage_Ground(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Stage_Ground::~Stage_Ground()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Stage_Ground::Draw()
{
	Object3D::Draw();
}
