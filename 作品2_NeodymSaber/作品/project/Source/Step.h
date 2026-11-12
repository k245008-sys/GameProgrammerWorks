#pragma once
#include "Object3D.h"
class Step :public Object3D
{
public:
	Step(const VECTOR& _pos);
	Step(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Step();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

