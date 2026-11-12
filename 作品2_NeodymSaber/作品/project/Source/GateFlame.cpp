#include "GateFlame.h"
#include"StageManager.h"
#include<assert.h>

GateFlame::GateFlame(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;
}

GateFlame::GateFlame(const VECTOR& _pos, const VECTOR& _rot, int _hModel):GateFlame(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

GateFlame::~GateFlame()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void GateFlame::Draw()
{
	Object3D::Draw();
}
