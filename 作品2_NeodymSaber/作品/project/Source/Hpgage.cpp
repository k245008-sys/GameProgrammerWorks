#include "HpGage.h"
#include"UiValue.h"
#include"Player.h"
#include<assert.h>

HpGage::HpGage()
{
	hImage = -1;
	hp = 0;
	scale = 0.0f;

	onehpImage = -1;

	onehpbackImage = -1;

	hpbackImage = -1;
	pich = false;
}

HpGage::HpGage(VECTOR2I Pos, int image, int flameimage)
{
	onehpImage = LoadGraph("data/texture/HP_gage_ver3-1.png");
	assert(onehpImage >= 0);

	onehpbackImage = LoadGraph("data/texture/HP_gage_1back.png");
	assert(onehpbackImage >= 0);

	hpbackImage = LoadGraph("data/texture/HP_gageback.png");
	assert(hpbackImage >= 0);

	pos = Pos;

	hImage = image;
	
	Flameimage = flameimage;
}

HpGage::~HpGage()
{
	if (onehpImage < 0)
	{
		DeleteGraph(onehpImage);
	}

	if (onehpbackImage < 0)
	{
		DeleteGraph(onehpbackImage);
	}

	if (hpbackImage < 0)
	{
		DeleteGraph(hpbackImage);
	}
}

void HpGage::Update()
{
	//velocity += DegToRad(80.0f * (1.0f / 10.0f));
	if (hp > 4)
	{
		_type = PLAYER_HP::NOM_HP;
	}
	if (hp < 4&&hp > 1)
	{
		_type = PLAYER_HP::PINCH_HP;
	}

	if (hp < 2)
	{
		_type = PLAYER_HP::DENGER_HP;
	}
}

void HpGage::Draw()
{
	for (int i = 0; i < 6; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		SetDrawBright(105, 105, 105);
		if (i < 1)
		{
			DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpbackImage, true, false);
		}
		else
			DrawRectGraph(((int)pos.x - 4) + 98 * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hpbackImage, true, false);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	Player* player = FindGameObject<Player>();

	hp = player->GetHP();

	nom_velocity += DegToRad(80.0f * (1.0f / 60.0f));
	float prmi = 12.0f * abs(cosf(nom_velocity));

	velocity += DegToRad(80.0f * (1.0f / 30.0f));
	float prmf = 12.0f * abs(cosf(velocity));

	scale_velocity += DegToRad(80.0f * (1.0f / 10.0f));
	float prm = 12.0f * abs(cosf(scale_velocity));

	switch (_type)
	{
	case PLAYER_HP::NOM_HP:
		for (int i = 0; i < hp; i++)
		{
			if (i < 1)
			{
				DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpImage, true, false);
			}
			else
				DrawRectGraph(((int)pos.x - 4) + 98 * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hImage, true, false);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prmi);
		SetDrawBright(247, 193, 20);
		for (int i = 0; i < hp; i++)
		{
			for (int s = 0; s < 5; s++)
			{
				if (i < 1)
				{
					DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpImage, true, false);
				}
				else
					DrawRectGraph(((int)pos.x - 4) + 98 * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hImage, true, false);
			}
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case PLAYER_HP::PINCH_HP:

		SetDrawBright(220, 203, 24);
		for (int i = 0; i < hp; i++)
		{
			if (i < 1)
			{
				DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpbackImage, true, false);
			}
			else
				DrawRectGraph(((int)pos.x - 4) + 98 * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hpbackImage, true, false);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prmf);
		SetDrawBright(220, 203, 24);
		for (int i = 0; i < hp; i++)
		{
			for (int s = 0; s < 5; s++)
			{
				if (i < 1)
				{
					DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpbackImage, true, false);
				}
				else
					DrawRectGraph(((int)pos.x - 4) + 98 * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hpbackImage, true, false);
			}
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	case HpGage::PLAYER_HP::DENGER_HP:

		SetDrawBright(158, 61, 63);
		DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpbackImage, true, false);
		SetDrawBright(255, 255, 255);

		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prm);
		for (int i = 0; i < 20; i++)
		{
			SetDrawBright(158, 61, 63);
			DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpbackImage, true, false);
			SetDrawBright(255, 255, 255);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	}
	/*
	if (hp < 2)
	{
		pich = true;
	}
	else
		pich = false;

	for (int i = 0; i < hp; i++)
	{
		if (i < 1)
		{
			if (!pich)
			{
			DrawRectGraph((int)pos.x - 2, (int)pos.y - 5, 0, 0, HP_GAGE_ONE_FOTE_SIZEX, HP_GAGE_ONE_FOTE_SIZEY, onehpImage, true, false);
			}
			else
			{

			}

		}
		else
			DrawRectGraph(((int)pos.x - 4) + 98.9f * i, (int)pos.y, 0, 0, HP_GAGE_FOTE_SIZEX, HP_GAGE_FOTE_SIZEY, hImage, true, false);
	}
	*/
	DrawRectGraph((int)pos.x, (int)pos.y, 0, 0, HP_GAGE_FLAME_FOTE_SIZEX, HP_GAGE_FLAME_FOTE_SIZEY, Flameimage, true, false);

}