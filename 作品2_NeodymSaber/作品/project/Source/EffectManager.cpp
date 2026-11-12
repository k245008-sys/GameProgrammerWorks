#include "EffectManager.h"
#include <assert.h>
#include <EffekseerForDXLib.h>
#include "EffectBase.h"
#include "EffectValue.h"

EffectManager::EffectManager(SceneBase* _scene)
{
	effects.clear();
	hEffects.insert({ "Hit", LoadEffekseerEffect("data/effect/Hit.efk") });
	hEffects.insert({ "AttractRangeRed", LoadEffekseerEffect("data/effect/efk/Hitmark_red.efk") });
	hEffects.insert({ "SnapUnionBlue", LoadEffekseerEffect("data/effect/efk/Hitmark_ble2.efkefc") });
	hEffects.insert({ "SnapUnionRed", LoadEffekseerEffect("data/effect/Hitmark_led.efkefc") });
	hEffects.insert({ "Shot", LoadEffekseerEffect("data/effect/shot.efkefc") });
	for (auto& e : hEffects)
		assert(e.second >= 0);
}

EffectManager::~EffectManager()
{
	Reset();
	for (auto& e : hEffects)
		DeleteEffekseerEffect(e.second);
	hEffects.clear();
}

void EffectManager::Update()
{
	for (auto& effect : effects)
		effect->Update();

	for (int i = 0; i < effects.size(); i++)
	{
		if (!effects[i]->GetIsPlaying() &&
			!effects[i]->GetIsLoop())
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
		}
	}

	//effekseerにより再生中のエフェクトを更新する
	UpdateEffekseer3D();
}

void EffectManager::Draw()
{
	// ビルボードを3D空間で正しく表示するため
	SetWriteZBuffer3D(FALSE);

	//DXライブラリのカメラとeffekseeerのカメラを同期する
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	for (auto& effect : effects)
		effect->Draw();
}

void EffectManager::Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const VECTOR& _scale)
{
	EffectSetting info = GetSetting(_type);
	info.scale *= _scale;
	effects.emplace_back(new EffectBase(_type, _pos, _rot, info, hEffects[_type]));
}

void EffectManager::Create(const std::string& _type, VECTOR* _pos, const VECTOR& _rot, const VECTOR& _scale)
{
	EffectSetting info = GetSetting(_type);
	info.scale *= _scale;
	effects.emplace_back(new EffectBase(_type, _pos, _rot, info, hEffects[_type]));
}

void EffectManager::Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const float& _scale)
{
	Create(_type, _pos, _rot, VGet(_scale, _scale, _scale));
}

void EffectManager::SetScale(const std::string& _type, const VECTOR& _scale)
{
	for (auto& effect : effects)
	{
		if (effect->GetType() == _type)
			effect->SetScale(_scale);
	}
}

void EffectManager::Delete(const std::string& _type)
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->GetType() == _type)
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
		}
	}
}

void EffectManager::Delete(VECTOR* _pos)
{
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->GetParentPos() == _pos)
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
			break;
		}
	}
}

void EffectManager::Reset()
{
	for (auto& e : effects)
		e->Stop();
	std::vector<EffectBase*>().swap(effects);
	effects.clear();
}

EffectSetting EffectManager::GetSetting(const std::string& _type)
{
	EffectSetting info = EGet();
	if (_type == "Hit")
		info = EFFECT_HIT_SETTING;
	if (_type == "AttractRangeRed")
		info = EFFECT_ATTRACT_RANGE_RED_SETTING;
	if (_type == "SnapUnionBlue" ||
		_type == "SnapUnionRed")
		info = EFFECT_SNAP_UNION_SETTING;
	if (_type == "Shot")
		info = EFFECT_SHOT_SETTING;
	return info;
}
