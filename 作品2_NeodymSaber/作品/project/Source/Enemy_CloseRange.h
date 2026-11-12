#pragma once
#include "EnemyBase.h"

/*
	‹ß‹——£UŒ‚‚¾‚¯‚Ì“GƒNƒ‰ƒX
	ˆ»•”
*/

class Enemy_CloseRange : public EnemyBase
{
public:
	Enemy_CloseRange(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot = VZero);
	~Enemy_CloseRange();
	void Update()override;
	void Draw()override;

private:
	void Init()override;
};