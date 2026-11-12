#include "ScoreManager.h"
#include "../Library/Time.h"
#include "ColorValue.h"
#include <assert.h>
#include "ScoreValue.h"
#include <algorithm>
#include "../Library/myDxLib.h"
#include <fstream>
#include <string>

ScoreManager::ScoreManager(SceneBase* _scene)
{
	hImages[0] = LoadGraph("data/texture/1st.png");
	hImages[1] = LoadGraph("data/texture/2nd.png");
	hImages[2] = LoadGraph("data/texture/3rd.png");

	numImage = LoadGraph("data/texture/num03.png");

	score = 0;
	currentCombo = 0;
	yShake = 0;
	totalCombo = 0;
	comboTime = 0;
	elapsedTime = 0;
	doComboTime = true;
	doCountTime = false;
	ranking = LoadRanking();
	std::sort(ranking.begin(), ranking.end(), std::greater<int>());
}

ScoreManager::~ScoreManager()
{
	for (int i = 0; i< RANKING_MAX; i++)
		DeleteGraph(hImages[i]);
	DeleteGraph(numImage);
}

void ScoreManager::Update()
{
	// クリアまで現実の経過時間を足す
	if(doCountTime)
	elapsedTime += Time::RealDeltaTime();

	//縦揺れの処理
	if (yShake > 0)
	{
		yShake -= 2.5f;
	}

	// コンボ持続時間(ゲーム内の経過速度)
	if (comboTime > 0)
	{
		if(doComboTime)
		comboTime -= Time::GameDeltaTime();
	}
	else
	{
		currentCombo = 0;
		comboTime = 0;
	}

	if (currentCombo > 999)
		currentCombo = 999;
	if (totalCombo > 999)
		totalCombo = 999;
}

void ScoreManager::Draw()
{
}

void ScoreManager::AddOneCurrentCombo()
{
	currentCombo++;
	if (currentCombo >= TOTAL_COMBO_ENABLE_ADD_CURRENT_COMBO_NUM)
		totalCombo++;
	yShake = 5;
	comboTime = COMBO_TIME;
}

void ScoreManager::ResetCurrentCombo()
{
	currentCombo = 0;
	comboTime = 0;
}

void ScoreManager::Reset()
{
	currentCombo = 0;
	totalCombo = 0;
	comboTime = 0;
	elapsedTime = 0.0f;
	doCountTime = false;
}

void ScoreManager::CalcRanking(const int& _score)
{
	score = _score;
	ranking = LoadRanking();
	int size = (int)ranking.size();
	ranking.emplace_back(_score);
	std::sort(ranking.begin(), ranking.end(), std::greater<int>());
	ranking.resize(size);
	SaveRanking(ranking);
}

void ScoreManager::DrawRanking(const VECTOR2& _leftUp)
{
	float space = RANKING_SPACE_X;
	for (int i = 0; i < (int)ranking.size(); i++)
	{
		VECTOR2 unitPos = VECTOR2(_leftUp.x + space * i, _leftUp.y);
		DrawRotaGraphF(unitPos.x, unitPos.y, 1.0, 0.0, hImages[i], true);
		int sc = ranking[i];
		int dig = 0;
		int copy = sc;
		VECTOR2 pos = unitPos + VECTOR2(50, -70);
		int count = 0;
		int cpy = copy;
		while (cpy > 0)
		{
			cpy /= 10;
			count++;
		}
		pos.x += count * ONE_COMBO_FOTE_SIZEX;
		while (copy > 0)
		{
			DrawRectGraphF(pos.x + (-ONE_COMBO_FOTE_SIZEX * dig), pos.y, copy % 10 * ONE_COMBO_FOTE_SIZEX, 0, ONE_COMBO_FOTE_SIZEX, COMBO_FOTE_SIZEY, numImage, true, false);
			copy /= 10;
			dig++;
		}
	}
}

void ScoreManager::AddDefaultRanking(std::vector<int>& _scores)
{
	int size = (int)(sizeof(DEFAULT_RANK_SCORE) / sizeof(DEFAULT_RANK_SCORE[0]));
	for (int s = 0; s < size; s++)
	{
		_scores.emplace_back(DEFAULT_RANK_SCORE[s]);
	}
}

int ScoreManager::GenerateHash(int _score)
{
	int h = (_score * 31 + 23273) % 10000 * 6 / 3;
	h += h / 32;
	return h;
}

void ScoreManager::SaveRanking(const std::vector<int>& _scores)
{
	std::ofstream file("ranking.dat");
	if (!file) return;

	for (int sc : _scores)
	{
		int hash = GenerateHash(sc);
		file << sc << " " << hash << "\n";
	}
}

std::vector<int> ScoreManager::LoadRanking()
{
	std::vector<int> scores;
	std::ifstream file("ranking.dat");
	if (!file) // ファイルなしなら初期化
	{
		AddDefaultRanking(scores);
		std::sort(ranking.begin(), ranking.end(), std::greater<int>());
		SaveRanking(scores);
		return scores;
	}

	for (int r = 0; r < RANKING_MAX; r++)
	{
		int sc = 0;
		int hash = 0;
		if (!(file >> sc >> hash))
			break;

		if (hash == GenerateHash(sc))
		{
			scores.emplace_back(sc);
		}
	}

	// 読み込めなかった分
	while ((int)scores.size() < RANKING_MAX)
	{
		AddDefaultRanking(scores);
		std::sort(ranking.begin(), ranking.end(), std::greater<int>());
		scores.resize(RANKING_MAX);
		std::remove("ranking.dat");
		SaveRanking(scores);
	}
	return scores;
}
