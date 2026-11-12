#include "Ceiling.h"
#include"StageManager.h"
#include <assert.h>

Ceiling::Ceiling(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Ceiling::Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :Ceiling(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Ceiling::~Ceiling()
{
	if(hModel < 0)
	MV1DeleteModel(hModel);
}

void Ceiling::Draw()
{
	Object3D::Draw();
}
