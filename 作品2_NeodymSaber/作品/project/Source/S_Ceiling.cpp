#include "S_Ceiling.h"
#include"StageManager.h"
#include <assert.h>

S_Ceiling::S_Ceiling(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

S_Ceiling::S_Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :S_Ceiling(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

S_Ceiling::~S_Ceiling()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void S_Ceiling::Draw()
{
	Object3D::Draw();
}
