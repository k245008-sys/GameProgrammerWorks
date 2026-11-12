#include "C_Ceiling.h"
#include"StageManager.h"
#include <assert.h>

C_Ceiling::C_Ceiling(const VECTOR& _pos)
{
	hModel = MV1LoadModel("data/model/StageObjects/Ceiling/cei_C.mv1");
	assert(hModel >= 0);

	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

C_Ceiling::C_Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel) :C_Ceiling(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

C_Ceiling::~C_Ceiling()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void C_Ceiling::Draw()
{
	Object3D::Draw();
}
