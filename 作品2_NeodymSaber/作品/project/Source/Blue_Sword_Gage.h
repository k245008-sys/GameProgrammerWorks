#pragma once
#include "GageBase.h"
class Blue_Sword_Gage :public GageBase
{
public:
	Blue_Sword_Gage();
	Blue_Sword_Gage(VECTOR2I Pos, int image, int flameimage);
	~Blue_Sword_Gage();

	void Update() override;
	void Draw() override;

private:
	int blueswordImage;
	int bottrn;
	float velocity;
};

