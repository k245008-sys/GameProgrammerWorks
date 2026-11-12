#include "Square.h"
#include"StageManager.h"
#include<assert.h>

Square::Square(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Square::Square(const VECTOR& _pos, const VECTOR& _rot, int _hModel):Square(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Square::~Square()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Square::Draw()
{
	Object3D::Draw();
}
