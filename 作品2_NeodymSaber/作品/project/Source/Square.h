#pragma once
#include "Object3D.h"
class Square :public Object3D
{
public:
	Square(const VECTOR& _pos);
	Square(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Square();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

