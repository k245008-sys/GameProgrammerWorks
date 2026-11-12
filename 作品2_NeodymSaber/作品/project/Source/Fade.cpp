#include "Fade.h"
#include "../Library/myDxLib.h"
#include "../Library/Time.h"
#include "config.h"

Fade::Fade()
{
	time = 0.0f;
	color = GetColor(0,0,0);
}

void Fade::Update()
{
	if (time > 0)
	{
		time -= Time::GameDeltaTime();
	}
	else
	{
		time = 0;
		color = GetColor(0, 0, 0);
	}
}

void Fade::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * alpha));
	DrawBox(0, 0, 1920, 1080, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
