#pragma once
#include "Object3D.h"
class W_Gate :public Object3D
{
public:
	W_Gate(const VECTOR& _pos);
	W_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~W_Gate();
	void Update()override;
	void Draw()override;

	void Reset();
private:
	bool open;
	bool anopen;
	int test;
	bool gateopenstate;
};

