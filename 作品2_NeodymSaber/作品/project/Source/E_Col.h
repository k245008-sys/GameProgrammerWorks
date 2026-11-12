#pragma once
#include "Object3D.h"
class E_Col :public Object3D
{
public:
	E_Col(const VECTOR& _pos);
	E_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~E_Col();
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

