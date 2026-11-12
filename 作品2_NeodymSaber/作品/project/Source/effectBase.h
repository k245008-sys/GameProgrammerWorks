#pragma once
#include "EffectManager.h"
#include "EffectValue.h"
#include "Object3D.h"

class EffectBase {
public:
	EffectBase(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot, const EffectSetting& _info, const int& _handle);
	EffectBase(const std::string& _type, VECTOR* _pos, const VECTOR& _rot, const EffectSetting& _info, const int& _handle);
	virtual ~EffectBase();
	virtual void Update();
	virtual void Draw();

	std::string GetType() { return type; }
	EffectSetting GetInfo() { return info; }
	VECTOR GetPos() { return transform.position; }
	VECTOR GetRot() { return transform.rotation; }
	VECTOR GetScale() { return transform.scale; }
	bool GetIsLoop() { return info.isLoop; }
	bool GetIsPlaying() { return isPlaying; }
	VECTOR* GetParentPos() { return parentPos; }

	void SetScale(const VECTOR& _scale) { transform.scale = _scale; }
	void Stop();

protected:
	void Play();

	std::string type;
	int hEffect;
	int hPlayingEffect;
	Transform transform;
	EffectSetting info;
	float elapsedTime;
	bool isPlaying;
	VECTOR* parentPos;
};