#pragma once
#include "Object3D.h"
class Col_Slope :public Object3D
{
public:
	Col_Slope(const VECTOR& _pos);
	Col_Slope(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Col_Slope();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

