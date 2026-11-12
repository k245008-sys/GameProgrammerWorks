#pragma once
#include"InputManager.h"
#include "../Library/myDxLib.h"

namespace
{
	const float GAME_OVER_FOTO_SIM_SIZE = 960.0f;

	enum GameOverState
	{
		STAGING,
		SELECT,
	};

	enum GameOverFote
	{
		GAMEOVER_FOTE,
		FADE_FOTE,
		FLAME_RIGHT,
		FLAME_LEFT,
		GAMEOVER_FOTE_MAX,
	};
}

class GameOver
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Draw();
	void Reset();

private:
	InputManager* input;

	GameOverState state;

	int hImage[GAMEOVER_FOTE_MAX];
	float velocity = 0.0f;

	VECTOR2 scaletime;

	int  alpha_Num;

	int backalupa_Num;
	int blackalupa_Num;
};

