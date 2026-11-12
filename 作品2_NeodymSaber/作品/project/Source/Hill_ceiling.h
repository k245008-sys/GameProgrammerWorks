#pragma once
#include "Object3D.h"
class Hill_ceiling :public Object3D
{
public:
	Hill_ceiling(const VECTOR& _pos);
	Hill_ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Hill_ceiling();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

