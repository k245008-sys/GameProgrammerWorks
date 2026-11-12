#include "Sky.h"
#include <assert.h>

Sky::Sky()
{
	pos = VGet(0, 500, 0);
	sca = VGet(3.0f, 3.0f, 3.0f);
	rot = VZero;

	hModel = MV1LoadModel("data\\model\\sky\\Stage00_sky.mv1");
	assert(hModel >= 0);
}

Sky::~Sky()
{
	MV1DeleteModel(hModel);
}

void Sky::Update()
{
	rot.y += 0.001;
}

void Sky::Draw()
{
	SetCameraNearFar(100.0f, 150000.0f);

	SetWriteZBuffer3D(TRUE);

	MATRIX mS = MGetScale(sca);
	MATRIX mR = MGetRotY(rot.y);
	MATRIX mT = MGetTranslate(pos);

	MATRIX m = MMult(mS, mR);
	m = MMult(m, mT);

	MV1SetMatrix(hModel, m);

	MV1DrawModel(hModel);
}
