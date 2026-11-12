#pragma once
#include "Object3D.h"
class Ceiling :public Object3D
{
public:
	Ceiling(const VECTOR& _pos);
	Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Ceiling();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};
