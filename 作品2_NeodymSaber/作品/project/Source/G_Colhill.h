#pragma once
#include "Object3D.h"
class G_Colhill :
    public Object3D
{
public:
	G_Colhill(const VECTOR& _pos);
	G_Colhill(const VECTOR& _pos, const VECTOR& _rot, int _hModel);
	~G_Colhill();
	void Update()override {};
	void Draw()override;
	void Reset() {};
};

