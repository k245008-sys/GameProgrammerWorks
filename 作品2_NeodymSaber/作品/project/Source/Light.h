#pragma once
#include "Object3D.h"

/*
	ライト全般の管理クラス
*/

class Player;

class Light : public Object3D
{
public:
	Light();
	void AssignFindObjToField()override;
	~Light();
	void Update()override;
	void Draw()override;

private:
	Player* player;

	int hDirLight;
	int hPointLight;
};