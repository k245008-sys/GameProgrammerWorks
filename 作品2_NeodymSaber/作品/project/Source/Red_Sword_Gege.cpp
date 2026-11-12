#include "Red_Sword_Gege.h"
#include"UiValue.h"
#include "Player.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include<assert.h>

Red_Sword_Gege::Red_Sword_Gege()
{
	redswordImage = -1;
	bottrn = -1;
	isApple = false;
}

Red_Sword_Gege::Red_Sword_Gege(VECTOR2I Pos, int image, int flameimage)
{
	redswordImage = LoadGraph("data/texture/red_meta-1back.png");
	assert(redswordImage >= 0);

	bottrn = LoadGraph("data/texture/red_botan_ver3-1.png");
	assert(bottrn >= 0);

	pos = Pos;
	hImage = image;
	Flameimage = flameimage;
}

Red_Sword_Gege::~Red_Sword_Gege()
{
	if (bottrn > 0)
	{
		DeleteGraph(bottrn);
	}

	if (redswordImage > 0)
	{
		DeleteGraph(redswordImage);
	}
}

void Red_Sword_Gege::Update()
{
	velocity += DegToRad(80.0f * (1.0f / 15.0f));
}

void Red_Sword_Gege::Draw()
{
	SetDrawBright(105, 105, 105);
	DrawRectGraph((int)pos.x - 1, (int)pos.y + 4, 0, 0, SWORD_GAGE_FOTE_SIZEX, SWORD_GAGE_FOTE_SIZEY, redswordImage, true, false);
	SetDrawBright(255, 255, 255);

	Player* player = FindGameObject<Player>();
	Sword_Throw* sw_throw = player->GetSword_Throw();
	int rightX = 547 - 65;
	float rate = sw_throw->GetAttractGaugeAmount() / SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX;
	int drawW = (int)(rightX * rate);
	DrawRectGraph((int)pos.x + rightX - drawW, (int)pos.y, rightX - drawW, 0, drawW, SWORD_GAGE_FOTE_SIZEY, hImage, true, false);

	DrawRectGraph((int)pos.x + 1, (int)pos.y + 2, 0, 0, SWORD_GAGE_FOTE_SIZEX, SWORD_GAGE_FOTE_SIZEY, Flameimage, true, false);

	DrawRectGraph((int)pos.x + 445, (int)pos.y, 0, 0, 100, 73, bottrn, true, false);

	isApple = sw_throw->GetCurrentStateName() == "Pierced";
	float prm = 12.0f * abs(cosf(velocity));
/*
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
