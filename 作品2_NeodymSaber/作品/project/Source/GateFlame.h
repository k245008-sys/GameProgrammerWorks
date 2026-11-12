#pragma once
#include "Object3D.h"
class GateFlame :public Object3D
{
public:
	GateFlame(const VECTOR& _pos);
	GateFlame(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~GateFlame();
	void Update()override {};
	void Draw()override;
};