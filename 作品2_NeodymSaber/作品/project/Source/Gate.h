#pragma once
#include "Object3D.h"
class Gate :public Object3D
{
public:
	Gate(const VECTOR& _pos);
	Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Gate();
	void Update()override {};
	void Draw()override;
};

