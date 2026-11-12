#include "OffScreenEnemyGuid.h"
#include "OffScreenEnemyGuidValue.h"
#include "EnemyBase.h"
#include "Player.h"
#include "ColorValue.h"

OffScreenEnemyGuid::OffScreenEnemyGuid(EnemyBase* _target, const int& _hModel)
{
	hModel = _hModel;
	target = _target;
	player = nullptr;
	transform.scale = OFF_SCREEN_ENEMY_GUID_SCALE;
}

OffScreenEnemyGuid::~OffScreenEnemyGuid()
{
}

void OffScreenEnemyGuid::Update()
{
	VECTOR dist = VNorm(target->GetPos() - player->GetPos());
	VECTOR diffRot = VZero;
	diffRot.z = -atan2f(dist.y, sqrtf(dist.x * dist.x + dist.z * dist.z));
	diffRot.y = atan2f(dist.x, dist.z);
	transform.rotation = diffRot;
	transform.position = player->GetPos()
		+ OFF_SCREEN_ENEMY_GUID_ADJUST_BASE_POS
		+ dist * OFF_SCREEN_ENEMY_GUID_DIST_TO_PLAYER;
}

void OffScreenEnemyGuid::Draw()
{
	COLOR_F dif = target->GetModelColor();
	COLOR_F amb = target->GetAmbColor();
	MV1SetMaterialDifColor(hModel, 0, dif - GetColorF(0, 0, 0, 1.0f - OFF_SCREEN_ENEMY_GUID_ALPHA));
	//MV1SetMaterialAmbColor(hModel, 0, amb);

	MATRIX mat = MGetScale(transform.scale);
	mat *= MGetRotZ(transform.rotation.z);
	mat *= MGetRotX(transform.rotation.x);
	mat *= MGetRotY(transform.rotation.y + DEGREE * 90);
	mat *= MGetTranslate(transform.position);
	MV1SetMatrix(hModel, mat);
	MV1DrawModel(hModel);
}
