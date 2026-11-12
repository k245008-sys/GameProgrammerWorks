#include "Blue_Sword_Gage.h"
#include "UiValue.h"
#include "../Library/Time.h"
#include"Player.h"
#include"PlayerValue.h"
#include<assert.h>

Blue_Sword_Gage::Blue_Sword_Gage()
{
	blueswordImage = -1;
	bottrn = -1;
	velocity = 0.0f;
}

Blue_Sword_Gage::Blue_Sword_Gage(VECTOR2I Pos, int image, int flameimage)
{
	blueswordImage = LoadGraph("data/texture/red_meta-1back.png");
	assert(blueswordImage >= 0);

	bottrn = LoadGraph("data/texture/blue_botan_ver3-1.png");
	assert(bottrn >= 0);

	pos = Pos;
	hImage = image;
	Flameimage = flameimage;
}

Blue_Sword_Gage::~Blue_Sword_Gage()
{
	if (bottrn > 0)
	{
		DeleteGraph(bottrn);
	}

	if (blueswordImage > 0)
	{
		DeleteGraph(blueswordImage);
	}
}

void Blue_Sword_Gage::Update()
{
}

void Blue_Sword_Gage::Draw()
{
	SetDrawBright(105, 105, 105);
	DrawRectGraph((int)pos.x - 5, (int)pos.y + 4, 0, 0, SWORD_GAGE_FOTE_SIZEX, SWORD_GAGE_FOTE_SIZEY, blueswordImage, true, true);
	SetDrawBright(255, 255, 255);

	Player* player = FindGameObject<Player>();
	float rate = player->GetAttractGaugeAmount() / PLAYER_ATTRACT_GAUGE_AMOUNT_MAX;
	float adjustX = 70;
	DrawRectGraph((int)pos.x + (int)adjustX, (int)pos.y, (int)adjustX, 0, (int)((SWORD_GAGE_FOTE_SIZEX - (int)adjustX) * rate), SWORD_GAGE_FOTE_SIZEY, hImage, true, false);

	DrawRectGraph((int)pos.x + 80, (int)pos.y + 1, 0, 0, SWORD_GAGE_FOTE_SIZEX, SWORD_GAGE_FOTE_SIZEY, Flameimage, true, false);

	DrawRectGraph((int)pos.x + 5, (int)pos.y, 0, 0, 100, 73, bottrn, true, false);

	/*
	isApple = sw_throw->GetCurrentStateName() == "Pierced";
	float prm = 12.0f * abs(cosf(velocity));

	if (isApple)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prm);
		SetDrawBright(230, 230, 250);
		for (int i = 0; i < 20; i++)
		{
			DrawRectGraph((int)pos.x + 445, (int)pos.y, 0, 0, 100, 73, bottrn, true, false);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	*/
}
