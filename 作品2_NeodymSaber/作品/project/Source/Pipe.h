#pragma once
#include "Object3D.h"
class Pipe :public Object3D
{
public:
	Pipe(const VECTOR& _pos);
	Pipe(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Pipe();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

