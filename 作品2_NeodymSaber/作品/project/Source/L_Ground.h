#pragma once
#include "Object3D.h"
class L_Ground :public Object3D
{
public:
	L_Ground(const VECTOR& _pos);
	L_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~L_Ground();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

