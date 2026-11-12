#include "avoid.h"
#include"Player.h"
#include"PlayerValue.h"
#include<assert.h>

avoid::avoid()
{
	bottrn = -1;
}

avoid::avoid(VECTOR2I Pos, int image, int flameimage)
{
	pos = Pos;
	hImage = image;
	Flameimage = flameimage;

	bottrn = LoadGraph("data/texture/kaihi_ui-1.png");
	assert(bottrn >= 0);
}

avoid::~avoid()
{
}

void avoid::Update()
{
	

}

void avoid::Draw()
{
	DrawRectGraph((int)pos.x + 31, (int)pos.y + 90, 0, 0, 32, 31, bottrn, true, true);

	int adjustY = 5;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	DrawRectGraph((int)pos.x, (int)pos.y, 0, adjustY, 93, 92, hImage, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	Player* player = FindGameObject<Player>();
	float rate = player->GetAvoidCoolDown() / PLAYER_AVOID_COOL_DOWN;
	float avoidsize = 92 * rate;

	SetDrawBright(50, 50, 50);
	DrawRectGraph((int)pos.x, (int)pos.y, 0, adjustY, 93, (int)avoidsize, hImage, true, false);
	SetDrawBright(255, 255, 255);

	DrawRectGraph((int)pos.x, (int)pos.y, 0, adjustY, 93, 92, Flameimage, true, true);


}
