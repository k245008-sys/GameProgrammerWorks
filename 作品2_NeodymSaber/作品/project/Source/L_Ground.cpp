#include "L_Ground.h"
#include"StageManager.h"
#include<assert.h>

L_Ground::L_Ground(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

L_Ground::L_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :L_Ground(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

L_Ground::~L_Ground()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void L_Ground::Draw()
{
	Object3D::Draw();
}
