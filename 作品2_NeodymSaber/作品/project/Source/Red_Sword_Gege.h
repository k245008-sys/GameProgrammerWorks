#pragma once
#include "GageBase.h"
class Red_Sword_Gege :public GageBase
{
public:
	Red_Sword_Gege();
	Red_Sword_Gege(VECTOR2I Pos, int image, int flameimage);
	~Red_Sword_Gege();

	void Update() override;
	void Draw() override;

	float DegToRad(const float& deg) { return deg * DX_PI_F / 180.0f; };

private:
	int redswordImage;
	int bottrn;
	float velocity;
	bool isApple;
};

