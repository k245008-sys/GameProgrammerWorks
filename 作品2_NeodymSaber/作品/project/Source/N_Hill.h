#pragma once
#include "Object3D.h"
class N_Hill :public Object3D
{
public:
	N_Hill(const VECTOR& _pos);
	N_Hill(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~N_Hill();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

