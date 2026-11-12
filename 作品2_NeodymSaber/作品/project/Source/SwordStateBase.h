#pragma once
#include "StateBase.h"
#include "EffectManager.h"

/*
	剣のステートの基底クラス
	綾部
*/

class SwordBase;
class DynamicObjBase;

class SwordStateBase : public StateBase
{
public:
	SwordStateBase() : effect(nullptr), parent(nullptr) {}
	virtual ~SwordStateBase() {}
	virtual void Update()override {}
	virtual void End()override {}

	void AssignFindObjToField()override
	{
		effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
	}

	void SetParent(DynamicObjBase* _parent)override;

protected:
	EffectManager* effect;
	SwordBase* parent;
};