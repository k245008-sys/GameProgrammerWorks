#pragma once
#include "../Library/gameObject.h"
#include "../Library/myDxLib.h"
#include <vector>

class UiBase;
class GageBase;

namespace
{
	enum  UI
	{
		COMBO,
		UI_MAX,
	};

	enum GAGE
	{
		COMBO_GAGE,
		SWORD_PIN,
		HP_GAGE,
		AVOID,
		BLUE_UI,
		RED_UI,
		RED_GAGE,
		BLUE_GAGE,
		GAGE_MAX,
	};

}

class UiManager :public GameObject
{
public:

	UiManager();
	~UiManager();

	void Update()override;
	void Draw()override;

	void SetEnable(const bool& _enable) { enable = _enable; }

private:

	//UIでの運営物
	VECTOR2I pos[UI_MAX];//UIの座標指定
	int hImage[UI_MAX];//UIの画像ハンドラ
	UiBase* ui[UI_MAX];
	std::vector<int> comboImages;

	bool enable;

	//GAGEでの運営物
	VECTOR2I gaegpos[GAGE_MAX];//GAGEの座標指定
	int gageImage[GAGE_MAX];//GAGEの画像ハンドラ
	int flameImage[GAGE_MAX];////GAGEフレームの画像ハンドラ
	GageBase* gage[GAGE_MAX];
};