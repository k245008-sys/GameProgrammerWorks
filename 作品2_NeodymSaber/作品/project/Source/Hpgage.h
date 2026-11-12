#pragma once
#include "GageBase.h"

class HpGage : public GageBase
{
public:
	HpGage();
	HpGage(VECTOR2I Pos, int image, int flameimage);
	~HpGage();

	void Update() override;
	void Draw() override;

	float DegToRad(const float& deg) { return deg * DX_PI_F / 180.0f; };

	enum class PLAYER_HP
	{
		NOM_HP,
		PINCH_HP,
		DENGER_HP,
	};
private:
	PLAYER_HP _type;
	int hImage;
	int hp;
	float scale;

	int onehpImage;

	int onehpbackImage;

	int hpbackImage;

	float velocity = 0.0f;

	float scale_velocity = 0.0f;

	float nom_velocity = 0.0f;
	bool pich;
};

