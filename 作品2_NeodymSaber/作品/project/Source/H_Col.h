#pragma once
#include "Object3D.h"
class H_Col :public Object3D
{
public:
	H_Col(const VECTOR& _pos);
	H_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~H_Col();
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

