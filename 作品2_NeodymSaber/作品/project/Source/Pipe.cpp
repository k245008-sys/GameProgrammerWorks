#include "Pipe.h"
#include"StageManager.h"
#include<assert.h>

Pipe::Pipe(const VECTOR& _pos)
{
	transform.position = _pos;
	transform.scale = STAGE_OBJECT_GROUND_SCALE;
}

Pipe::Pipe(const VECTOR& _pos, const VECTOR& _rot, int _hModel):Pipe(_pos)
{
	hModel = MV1DuplicateModel(_hModel);
	transform.rotation = _rot;
}

Pipe::~Pipe()
{
	if (hModel < 0)
		MV1DeleteModel(hModel);
}

void Pipe::Draw()
{
	Object3D::Draw();
}
