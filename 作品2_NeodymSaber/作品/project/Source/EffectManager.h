#pragma once
#include "../Library/gameObject.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "EffectValue.h"

class EffectBase;

class EffectManager :public GameObject {
public:
	EffectManager(SceneBase* _scene);
	void Init();
	~EffectManager();
	void Update()override;
	void Draw()override;

	void Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot,
		const VECTOR& _scale);
	void Create(const std::string& _type, VECTOR* _pos, const VECTOR& _rot,
		const VECTOR& _scale);
	void Create(const std::string& _type, const VECTOR& _pos, const VECTOR& _rot,
		const float& _scale = 1.0f);

	void SetScale(const std::string& _type, const VECTOR& _scale);

	void Delete(const std::string& _type);
	void Delete(VECTOR* _pos);
	void Reset();

private:
	EffectSetting GetSetting(const std::string& _type);

	std::vector<EffectBase*> effects;
	std::unordered_map<std::string, int> hEffects;
};