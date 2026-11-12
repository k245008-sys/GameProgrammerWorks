#pragma once
#include "Object3D.h"
class Slope_Col :public Object3D
{
public:
	Slope_Col(const VECTOR& _pos);
	Slope_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Slope_Col();
	void Update()override {};
	void Draw()override;
	void Reset() {};
protected:
	bool coll;
	bool push;
};

