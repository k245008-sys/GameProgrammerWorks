#pragma once
#include "Object3D.h"
class hand_rail :public Object3D
{
public:
	hand_rail(const VECTOR& _pos);
	hand_rail(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~hand_rail();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};


