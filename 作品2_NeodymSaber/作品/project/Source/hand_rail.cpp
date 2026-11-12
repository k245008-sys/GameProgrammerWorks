#include "hand_rail.h"
#include"StageManager.h"
#include<assert.h>

hand_rail::hand_rail(const VECTOR& _pos)
{

	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

hand_rail::hand_rail(const VECTOR& _pos, const VECTOR& _rot, int _hModel):hand_rail(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

hand_rail::~hand_rail()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void hand_rail::Draw()
{
	Object3D::Draw();
}
