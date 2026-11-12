#pragma once
#include "../Library/myDxLib.h"

namespace
{
	enum TitleState
	{
		FADE_IN,
		WAIT,
		FADE_OUT,
	};
}

class InputManager;
class ScoreManager;

class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	void Update();
	void Draw();

	float DegToRad(const float& deg) { return deg * DX_PI_F / 180.0f; };

private:
	void Reset();

	TitleState state;
	float fadeRate;
	float time;

	int logoImage = -1;
	int BotanLogo = -1; // ƒ^ƒCƒgƒ‹ƒƒS‰æ‘œ
	int backImage;
	float velocity = 0.0f;
	float scale;
	ScoreManager* score;
	InputManager* input;
};