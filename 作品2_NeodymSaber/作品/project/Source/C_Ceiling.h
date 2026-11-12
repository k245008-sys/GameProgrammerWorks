#pragma once
#include "Object3D.h"
class C_Ceiling :public Object3D
{
public:
	C_Ceiling(const VECTOR& _pos);
	C_Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~C_Ceiling();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

