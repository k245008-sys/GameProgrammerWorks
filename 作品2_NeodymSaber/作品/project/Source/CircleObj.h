#pragma once
#include "Object3D.h"

class CircleObj : public Object3D
{
public:
	CircleObj();
	~CircleObj();
	void Draw()override;
};