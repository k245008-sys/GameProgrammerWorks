#pragma once
#include"Object3D.h"
class Enemy_Gate :public Object3D
{
public:
	Enemy_Gate(const VECTOR& _pos);
	Enemy_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Enemy_Gate();
	void Update()override;
	void Draw()override;

	void Reset();
private:
	bool open;
	bool anopen;
	bool gateopenstate;
	int test;
};