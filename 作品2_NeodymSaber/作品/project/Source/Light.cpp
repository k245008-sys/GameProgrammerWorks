#include "Light.h"
#include "Player.h"

#include "LightValue.h"

Light::Light()
{
	player = nullptr;

	SetLightEnable(TRUE);
	SetLightDirection(MAIN_DIR_LIGHT_DIRECTION);
	SetLightDifColor(MAIN_DIR_LIGHT_DIF_COLOR);
	SetLightSpcColor(MAIN_DIR_LIGHT_SPC_COLOR);
	SetLightAmbColor(MAIN_DIR_LIGHT_AMB_COLOR);

	hDirLight = CreateDirLightHandle(SUB_DIR_LIGHT_DIRECTION);
	SetLightDifColorHandle(hDirLight, SUB_DIR_LIGHT_DIF_COLOR);

	hPointLight = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f),
		POINT_LIGHT_RANGE, POINT_LIGHT_ATTEN_ZERO, POINT_LIGHT_ATTEN_ONE, POINT_LIGHT_ATTEN_TWO);
}

void Light::AssignFindObjToField()
{
	player = FindGameObject<Player>();
}

Light::~Light()
{
	DeleteLightHandle(hDirLight);
	DeleteLightHandle(hPointLight);
}

void Light::Update()
{
	AssignFindObjToField();

	SetGlobalAmbientLight(GetColorF(1.0f,1.0f,1.0f,1.0f));
	SetLightDirectionHandle(hDirLight, SUB_DIR_LIGHT_DIRECTION);
	SetLightSpcColorHandle(hDirLight, SUB_DIR_LIGHT_SPC_COLOR);
	SetLightAmbColorHandle(hDirLight, SUB_DIR_LIGHT_AMB_COLOR);

	VECTOR pPos = player->GetPos();
	VECTOR pointPos = pPos + POINT_LIGHT_ADUST_POS;
	SetLightPositionHandle(hPointLight, pointPos);
}

void Light::Draw()
{
}
