#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class UiBase;

class UiManeger :public GameObject
{
public:
	UiManeger();
	~UiManeger();

	void Update()override;
	void Draw()override;
private:
	VECTOR2 pos;
	int hImage;
	UiBase* ui;
};