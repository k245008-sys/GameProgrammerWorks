#pragma once
#include "EnemyBase.h"

/*
	Ž©”š‚·‚é“GƒNƒ‰ƒX
	ˆ»•”
*/

class Enemy_Bomb : public EnemyBase
{
public:
	Enemy_Bomb(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot = VZero);
	~Enemy_Bomb();
	void Update()override;
	void Draw()override;

	void Damage(const VECTOR& _vel, const float& _time = ENEMY_DAMAGE_DEFAULT_TIME)override;
	void BeDead(const VECTOR& _vel)override;
	void Snap(const VECTOR& _snapPos, const float& _finishDist)override;

private:
	void Init()override;
	void ResetWasSnap()override;
};