#pragma once
#include "../Library/sceneBase.h"
#include "InputManager.h"
#include "../Library/myDxLib.h"

namespace
{
	enum ResultState
	{
		R_BLACKOUT,
		R_APPEAR,
		R_SELECT,
	};
}

class InputManager;
class ScoreManager;

class ResultScene
{
public:
	ResultScene();
	~ResultScene();
	void Update();
	void Draw();

	void Reset();

private:
	void DrawResult();

	InputManager* input;
	ScoreManager* score;

	ResultState state;

	int compImage;
	int resultImage;
	int numImage;
	int spaceImage;
	int rankImage[4];
	int backalupa_num;
	int alphaNum;

	float scoreAlphaRate;
	float rankingAlphaRate;
	float time;
};

