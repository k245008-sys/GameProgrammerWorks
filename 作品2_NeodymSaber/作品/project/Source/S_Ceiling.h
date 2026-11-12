#pragma once
#include "Object3D.h"
class S_Ceiling :public Object3D
{
public:
	S_Ceiling(const VECTOR& _pos);
	S_Ceiling(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~S_Ceiling();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

