#pragma once
#include "../Library/gameObject.h"


class ScoreManager;

class GageBase :public GameObject
{
public:
	GageBase();
	GageBase(VECTOR2I Pos, int image, int flameimage);
	~GageBase();

	virtual void Update() {};
	void Draw() {};
protected:
	ScoreManager* score;
	//画像ハンドラ
	int hImage;

	//フレームの画像ハンドラ
	int Flameimage;

	//位置座標
	VECTOR2I pos;

	//指定された画像のサイズ取得
	int imageSizeX;
	int imageSizeY;
};

