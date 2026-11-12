#pragma once
#include "Object3D.h"
class Hill : public Object3D
{
public:
	Hill(const VECTOR& _pos);
	Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Hill();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

