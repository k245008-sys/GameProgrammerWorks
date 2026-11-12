#pragma once
#include "Object3D.h"
class W_Col : public Object3D
{
public:
	W_Col(const VECTOR& _pos);
	W_Col(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~W_Col();
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

