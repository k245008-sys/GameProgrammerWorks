#pragma once
#include "Object3D.h"

class Stairs :public Object3D
{
public:
	Stairs(const VECTOR& _pos);
	Stairs(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Stairs();
	void Update()override;
	void Draw()override;
	void Reset() {};
protected:
	bool coll;
	bool push;
};

