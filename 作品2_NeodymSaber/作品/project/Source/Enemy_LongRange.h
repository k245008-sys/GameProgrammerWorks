#pragma once
#include "EnemyBase.h"

/*
	‰“‹——£UŒ‚‚¾‚¯‚Ì“GƒNƒ‰ƒX
	ˆ»•”
*/

class Enemy_LongRange : public EnemyBase
{
public:
	Enemy_LongRange(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot = VZero);
	~Enemy_LongRange();
	void Update()override;
	void Draw()override;

private:
	void Init()override;
};