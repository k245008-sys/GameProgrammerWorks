#pragma once
#include "../Library/myDxLib.h"

class DrawBox3D
{
public:
	void DrawFront(const VECTOR& _pos, const VECTOR& _size, const VECTOR& _rot, const unsigned int& _color, const int& _alpha);
};