#pragma once
#include "Object3D.h"
class N_Colhill :public Object3D
{
public:
	N_Colhill(const VECTOR& _pos);
	N_Colhill(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~N_Colhill();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};