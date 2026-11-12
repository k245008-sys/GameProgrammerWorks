#pragma once
#include "GageBase.h"

class Camera;
class Player;

class SwordPin :public GageBase
{
public:
	SwordPin();
	SwordPin(VECTOR2I Pos, int image, int flameimage);
	~SwordPin();

	void Update() override;
	void Draw() override;

private:
	Camera* camera;
	Player* sword;
	double extRate;//‚«o‚µ‚ÌŠg‘åŠp
	float flameAngle;//‚«o‚µ‚Ì‰ñ“]Šp
	int alpha_num;//“§‰ß—¦

	bool isAppear; // •\¦‚·‚é‚©
	float redSword;
	int swordImage;//Œ•‚Ìƒnƒ“ƒhƒ‰
	VECTOR2I gaugePos;
};