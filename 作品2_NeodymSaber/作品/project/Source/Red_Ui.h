#pragma once
#include "GageBase.h"
class Red_Ui :public GageBase
{
public:
	Red_Ui();
	Red_Ui(VECTOR2I Pos, int image, int flameimage);
	~Red_Ui();

	void Update() override;
	void Draw() override;
	float DegToRad(const float& deg) { return deg * DX_PI_F / 180.0f; };
private:
	int blueswordImage;
	int bottrn;
	float velocity;
};
