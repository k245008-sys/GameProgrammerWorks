#pragma once
#include"GageBase.h"

class avoid :public GageBase
{
public:
	avoid();
	avoid(VECTOR2I Pos, int image, int flameimage);
	~avoid();

	void Update() override;
	void Draw() override;

private:
	int bottrn;
};

