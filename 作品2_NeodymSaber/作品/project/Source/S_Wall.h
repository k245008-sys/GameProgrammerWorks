#pragma once
#include "Object3D.h"
class S_Wall :public Object3D
{
public:
	S_Wall(const VECTOR& _pos);
	S_Wall(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~S_Wall();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

