#pragma once
#include"Object3D.h"
class Player_Gate : public Object3D
{
public:
	Player_Gate(const VECTOR& _pos);
	Player_Gate(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Player_Gate();
	void Update()override;
	void Draw()override;

	void Reset();

private:
	bool gateopenstate = false;
	bool anopen = false;
	bool open = false;
};

