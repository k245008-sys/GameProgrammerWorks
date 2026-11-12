#pragma once
#include "Object3D.h"
class Hillend :public Object3D
{
public:
	Hillend(const VECTOR& _pos);
	Hillend(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Hillend();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

