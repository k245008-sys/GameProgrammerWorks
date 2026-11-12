#include "Red_Ui.h"
#include "Player.h"
#include"UiValue.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include<assert.h>

Red_Ui::Red_Ui()
{
	velocity = 0.0f;
}

Red_Ui::Red_Ui(VECTOR2I Pos, int image, int flameimage)
{
	pos = Pos;
	hImage = image;
	Flameimage = flameimage;
}

Red_Ui::~Red_Ui()
{
}

void Red_Ui::Update()
{
	velocity += DegToRad(80.0f * (1.0f / 15.0f));
}

void Red_Ui::Draw()
{

	Player* player = FindGameObject<Player>();
	Sword_Throw* sw_throw = player->GetSword_Throw();
	bool isApple = sw_throw->GetCurrentStateName() == "Pierced";

	float prm = (12.0f * 8) * abs(cosf(velocity));

	if (isApple)
	{

		for (int i = 0; i < 3; i++)
		{
			DrawRectGraph((int)pos.x + 460, ((int)pos.y - 20) - 15 * i, 0, 0, 155, 23, hImage, true, false);
		}

		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prm);
		for (int i = 0; i < 3; i++)
		{
			DrawRectGraph((int)pos.x + 460, ((int)pos.y - 20) - 15 * i, 0, 0, 155, 23, hImage, true, false);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRectGraph((int)pos.x + 345, (int)pos.y - 110, 0, 0, 258, 62, Flameimage, true, false);
	}
}
