#include "Hillend.h"
#include"StageManager.h"
#include<assert.h>

Hillend::Hillend(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Hillend::Hillend(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Hillend(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Hillend::~Hillend()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Hillend::Draw()
{
	Object3D::Draw();
}
