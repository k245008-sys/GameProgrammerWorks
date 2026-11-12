#include "CircleObj.h"
#include <assert.h>
#include "EnemyValue.h"

CircleObj::CircleObj()
{
	hModel = MV1LoadModel("data/model/circle.mv1");
	assert(hModel > 0);

	MV1SetMaterialDifColor(hModel, 0, ENEMY_JUDGE_START_DIST_CIRCLE_DIF_COLOR);
	MV1SetMaterialAmbColor(hModel, 0, ENEMY_JUDGE_START_DIST_CIRCLE_AMB_COLOR);
}

CircleObj::~CircleObj()
{
}

void CircleObj::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ENEMY_JUDGE_START_DIST_CIRCLE_ALPHA);
	Object3D::Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
