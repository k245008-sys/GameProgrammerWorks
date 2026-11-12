#include "EffectBase.h"
#include <EffekseerForDXLib.h>
#include "../Library/Time.h"

EffectBase::EffectBase(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const EffectSetting& _info, const int& _handle)
{
	type = _type;
	transform.position = _pos;
	transform.rotation = _rot;
	info = _info;
	transform.scale = info.scale;
	hEffect = _handle;
	hPlayingEffect = PlayEffekseer3DEffect(hEffect);
	elapsedTime = 0;
	isPlaying = false;
	parentPos = nullptr;
}

EffectBase::EffectBase(const std::string& _type, VECTOR* _pos, const VECTOR& _rot, const EffectSetting& _info, const int& _handle)
	: EffectBase(_type, *_pos, _rot, _info, _handle)
{
	parentPos = _pos;
}

EffectBase::~EffectBase()
{
	Stop();
}

void EffectBase::Update()
{
	elapsedTime += Time::GameDeltaTime();
	SetSpeedPlayingEffekseer3DEffect(hPlayingEffect, info.playSpeed);
	if (parentPos != nullptr)
		transform.position = *parentPos;
	SetPosPlayingEffekseer3DEffect(hPlayingEffect, transform.position.x, transform.position.y, transform.position.z);
	SetRotationPlayingEffekseer3DEffect(hPlayingEffect, transform.rotation.x, transform.rotation.y, transform.rotation.z);
	SetScalePlayingEffekseer3DEffect(hPlayingEffect, transform.scale.x, transform.scale.y, transform.scale.z);
	isPlaying = (IsEffekseer3DEffectPlaying(hPlayingEffect) == 0);
	if (!isPlaying && info.isLoop)
		Play();
}

void EffectBase::Draw()
{
}

void EffectBase::Stop()
{
	StopEffekseer3DEffect(hPlayingEffect);
}

void EffectBase::Play()
{
	hPlayingEffect = PlayEffekseer3DEffect(hEffect);
}
