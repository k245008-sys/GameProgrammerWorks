#pragma once
#include "StateBase.h"

/*
	敵ステートの基底クラス
	綾部
*/

class EnemyBase;
class Player;
class DynamicObjBase;
class SoundManager;

class EnemyStateBase : public StateBase
{
public:
	EnemyStateBase() : parent(nullptr), player(nullptr), sound(nullptr) {}
	virtual ~EnemyStateBase() {}
	virtual void Update()override {}
	virtual void Draw()override {}
	virtual void End()override {}

	EnemyBase* GetParent() { return parent; }
	Player* GetPlayer() { return player; }

	void SetParent(DynamicObjBase* _parent)override;
	void SetFind(Player* _player, SoundManager* _sound)
	{
		player = _player;
		sound = _sound;
	}

protected:
	EnemyBase* parent;
	Player* player;
	SoundManager* sound;
};