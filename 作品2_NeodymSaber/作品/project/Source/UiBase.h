#pragma once
#include "../Library/gameObject.h"


class ScoreManager;

class UiBase :public GameObject
{
public:
	UiBase();
	UiBase(VECTOR2I Pos, int image);
	~UiBase();

	virtual void Update() {};
	void Draw() {};
protected:
	//画像ハンドラ
	int hImage;

	//位置座標
	VECTOR2I pos;

	//指定された画像のサイズ取得
	int imageSizeX;
	int imageSizeY;
};

