#pragma once
#include "Object3D.h"
class H_Gate :public Object3D
{
public:
	H_Gate(const VECTOR& _pos);
	H_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~H_Gate();
	void Update()override;
	void Draw()override;

	void Reset();
private:
	bool open;
	bool anopen;
	int test;
	bool gateopenstate;
};

