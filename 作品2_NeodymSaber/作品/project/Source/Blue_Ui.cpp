#include "Blue_Ui.h"
#include "../Library/Time.h"
#include "UiValue.h"
#include<assert.h>
#include "Player.h"
#include "PlayerValue.h"

Blue_Ui::Blue_Ui()
{
	velocity = 0.0f;
	blueswordImage = -1;
	bottrn = -1;
}

Blue_Ui::Blue_Ui(VECTOR2I Pos, int image, int flameimage)
{
	pos = Pos;
	hImage = image;
	Flameimage = flameimage;
}

Blue_Ui::~Blue_Ui()
{
}

void Blue_Ui::Update()
{
	velocity += DegToRad(80.0f * (1.0f / 15.0f));
}

void Blue_Ui::Draw()
{
	Player* player = FindGameObject<Player>();
	bool isApple = player->GetCurrentStateName() == "Attract";
	float gagerate = player->GetAttractGaugeAmount() - PLAYER_ATTRACT_ATTACK_REDUCE_GAUGE;
	float prm = (12.0f * 8) * abs(cosf(velocity));

	if (isApple && gagerate > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			DrawRectGraph((int)pos.x + 40, ((int)pos.y - 20) - 15 * i, 0, 0, 155, 23, hImage, true, false);
		}

		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)prm);
		for (int i = 0; i < 3; i++)
		{
			DrawRectGraph((int)pos.x + 40, ((int)pos.y - 20) - 15 * i, 0, 0, 155, 23, hImage, true, false);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRectGraph((int)pos.x + 20, (int)pos.y - 110, 0, 0, 258, 62, Flameimage, true, false);
	}
}
