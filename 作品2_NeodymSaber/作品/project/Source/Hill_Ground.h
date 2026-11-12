#pragma once
#include "Object3D.h"
class Hill_Ground : public Object3D
{
public:
	Hill_Ground(const VECTOR& _pos);
	Hill_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Hill_Ground();
	void Update()override {};
	void Draw()override;
	void Reset() {};

protected:
	bool coll;
	bool push;
};