#pragma once
#include "Object3D.h"
#include"StageManager.h"

class Wall :public Object3D
{
public:
	Wall(const VECTOR& _pos);
	Wall(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	Wall();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

