#pragma once
#include "../Library/gameObject.h"

#include <vector>
#include "UiValue.h"

/*
	スコア、コンボ、経過時間など
	リザルト評価に関わる値を管理するクラス
	綾部
*/

namespace
{
	const float COMBO_TIME = 4.0f;
}

class ScoreManager : public GameObject
{
public:
	ScoreManager(SceneBase* _scene);
	~ScoreManager();
	void Update()override;
	void Draw()override;

	int GetScore() { return score; }
	int GetCurrentCombo() { return currentCombo; }
	int GetTotalCombo() { return totalCombo; }
	float GetyShake() { return yShake; }
	float GetComboTime() { return comboTime; }
	float GetElapsedTime() { return elapsedTime; }

	void SetDoComboTime(const bool& _isElapsed) { doComboTime = _isElapsed; }
	void SetDoCountTime(const bool& _doCountTime) { doCountTime = _doCountTime;}

	void AddOneCurrentCombo();
	void ResetCurrentCombo();
	void Reset();

	void CalcRanking(const int& _score);
	void DrawRanking(const VECTOR2& _leftUp);

private:
	void AddDefaultRanking(std::vector<int>& _scores);
	int GenerateHash(int _score);
	void SaveRanking(const std::vector<int>& _scores);
	std::vector<int> LoadRanking();

	int score;
	int currentCombo;	// 現在続いているコンボ数
	int totalCombo;	// コンボ総数
	float yShake;	   //コンボの横揺れ
	float comboTime; // コンボ持続残り時間
	float elapsedTime; // クリアまでの経過時間
	bool doComboTime;
	bool doCountTime;
	int numImage;

	std::vector<int> ranking;

	int hImages[3];
};