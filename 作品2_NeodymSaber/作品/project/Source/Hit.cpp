#include "Hit.h"
#include <assert.h>

Hit::Hit()
{
	appearanceTime = 0;
	position = VGet(0, 0, 0);
}

Hit::Hit(VECTOR pos, VECTOR rot, int eData)
{
	appearanceTime = 0;
	finishHandle = false;
	hEffectData = eData;
	position = pos;
	rotation = rot;
	hPlayingEffect = PlayEffekseer3DEffect(hEffectData);
}

Hit::~Hit()
{
	DeleteEffekseerEffect(hEffectData);
}

void Hit::Update()
{
	UpdateEffect();
}

void Hit::Draw()
{

}

void Hit::UpdateEffect()
{

	if (appearanceTime++ > 30) {
		finishHandle = true;
	}

	SetUpdate();
}

void Hit::SetUpdate()
{

	//再生中のエフェクトを移動する
	SetPosPlayingEffekseer3DEffect(hPlayingEffect, position.x, position.y, position.z);
	SetRotationPlayingEffekseer3DEffect(hEffectData, rotation.x, rotation.y, rotation.z);
}

bool Hit::Finish()
{
	return finishHandle;
}
