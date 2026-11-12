#pragma once
#include "GageBase.h"
class Combogage :public GageBase
{
public:
	Combogage();
	Combogage(VECTOR2I Pos, int image, int flameimage);
	~Combogage();

	void Update() override;
	void Draw() override;

private:
	int comboGage;
	float comboTime;//コンボ扇形表示の広さ
	int Comboname;
};

