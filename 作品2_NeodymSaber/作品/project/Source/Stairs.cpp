#include "Stairs.h"
#include "W_Col.h"
#include"StageManager.h"
#include <assert.h>

Stairs::Stairs(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GATE_SCALE;

	push = false;
	coll = false;
}

Stairs::Stairs(const VECTOR& _pos, const VECTOR& _rot, int _hModel) : Stairs(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Stairs::~Stairs()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Stairs::Update()
{

}

void Stairs::Draw()
{
		MATRIX mat = GetDrawMatrix();
		MV1SetMatrix(hModel, mat);

	//Object3D::Draw();
}
