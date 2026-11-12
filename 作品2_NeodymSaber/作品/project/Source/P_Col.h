#pragma once
#include "Object3D.h"
class P_Col :public Object3D
{
public:
	P_Col(const VECTOR& _pos);
	P_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~P_Col();
	void Update()override;
	void Draw()override;
	void Reset();

private:
	bool open;
	bool anopen;
	bool gateopenstate;
protected:
	bool coll;
	bool push;
};

