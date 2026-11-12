#pragma once
#include "Object3D.h"
class High_Col :public Object3D
{
public:
	High_Col(const VECTOR& _pos);
	High_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~High_Col();
	void Update()override {};
	void Draw()override;
	void Reset() {};
protected:
	bool coll;
	bool push;
};

