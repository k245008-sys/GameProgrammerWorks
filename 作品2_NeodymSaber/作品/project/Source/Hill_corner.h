#pragma once
#include "Object3D.h"
class Hill_corner :public Object3D
{
public:
	Hill_corner(const VECTOR& _pos);
	Hill_corner(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Hill_corner();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

