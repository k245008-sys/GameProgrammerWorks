#pragma once
#include "Object3D.h"
class F_Gate :public Object3D
{
public:
	F_Gate(const VECTOR& _pos);
	F_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~F_Gate();
	void Update()override;
	void Draw()override;

	void Reset();
private:
	bool open;
	bool anopen;
	bool gateopenstate;

	int test;
};

