#pragma once
#include"UiBase.h"
#include "../Library/gameObject.h"

#include <vector>

class ScoreManager;

class Combo : public UiBase
{
public:
	Combo();
	Combo(const VECTOR2I& Pos, std::vector<int> image);
	~Combo();

	void Update() override;
	void Draw() override;

private:
	ScoreManager* combo;
	std::vector<int> hImages;
	float addDigPosX;	//桁が増えても中央揃えにする
	float shakeY;	//縦揺れ値コピー
	int combo_Num;//コンボの表示桁
	int combo_num;//コンボ値コピー
};

