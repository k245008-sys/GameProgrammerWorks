#pragma once
#include "Object3D.h"
class F_Hill :public Object3D
{
public:
	F_Hill(const VECTOR& _pos);
	F_Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~F_Hill();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

