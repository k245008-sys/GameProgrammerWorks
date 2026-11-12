#include"StageManager.h"
#include "Step.h"
#include<assert.h>

Step::Step(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Step::Step(const VECTOR& _pos, const VECTOR& _rot, int _hModel) : Step(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Step::~Step()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Step::Draw()
{
	Object3D::Draw();
}
