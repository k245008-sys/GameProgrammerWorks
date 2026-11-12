#include "Combogage.h"
#include "UiValue.h"
#include "debugScreen.h"
#include"ScoreManager.h"
#include<assert.h>

Combogage::Combogage()
{
	comboTime = 0.0f;
	comboGage = -1;
	Comboname = 1;
}

Combogage::Combogage(VECTOR2I Pos, int image, int flameimage)
{

	comboGage = LoadGraph("data/texture/combo_siro1.png");
	assert(comboGage >= 0);

	Comboname = LoadGraph("data/texture/conbo-1.png");
	assert(Comboname >= 0);

	comboTime = 0;
	pos = Pos;
	hImage = image;
	Flameimage = flameimage;
	GetGraphSize(hImage, &imageSizeX, &imageSizeY);
}

Combogage::~Combogage()
{
	DeleteGraph(comboGage);
	DeleteGraph(Comboname);
}

void Combogage::Update()
{

}

void Combogage::Draw()
{
	score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();

	comboTime = score->GetComboTime();

	if (comboTime > 0)
	{
		float comboTimeRate = 35 + ((comboTime / COMBO_TIME) * 65);
		if (comboTimeRate >= 45)
		{
			DrawCircleGauge((int)pos.x + COMBO_GAGE_POS_SHIFTX, (int)pos.y + COMBO_GAGE_POS_SHIFTY, (double)comboTimeRate, hImage, 0, true, true);
		}
		else
		{
			SetDrawBright(255,0,0);
			DrawCircleGauge((int)pos.x + COMBO_GAGE_POS_SHIFTX, (int)pos.y + COMBO_GAGE_POS_SHIFTY, (double)comboTimeRate, comboGage, 0 , true , true);
			SetDrawBright(255, 255, 255);
		}

		DrawRectGraph((int)pos.x, (int)pos.y, 0, 0, imageSizeX, imageSizeY, Flameimage, true, true);
		DrawRectGraph((int)pos.x - 35, (int)pos.y - 5, 0, 0, imageSizeX, imageSizeY, Comboname, true, false);
	}
	//DebugPrintf(0, 500, "ExtRate : %.f", Combotime);
}
