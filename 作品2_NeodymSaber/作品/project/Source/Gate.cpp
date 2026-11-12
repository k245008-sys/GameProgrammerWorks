#include "Gate.h"
#include"StageManager.h"
#include<assert.h>
#include"Player.h"

Gate::Gate(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;
}

Gate::Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel) : Gate(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Gate::~Gate()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Gate::Draw()
{
	Object3D::Draw();
}
