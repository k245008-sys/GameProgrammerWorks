#pragma once
#include "Object3D.h"
#include"StageManager.h"

/*
	ステージの地面作成に必要なクラスの管理
	石井
*/

class Stage_Ground :public Object3D
{
public:
	Stage_Ground(const VECTOR& _pos);
	Stage_Ground(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~Stage_Ground();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

