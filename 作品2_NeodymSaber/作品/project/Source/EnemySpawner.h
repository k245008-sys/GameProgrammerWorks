#pragma once
#include "../Library/myDxLib.h"
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

/*
	敵スポーン処理クラス
	綾部
*/

struct SpawnerInfo
{
	std::string type;
	float timing;
	VECTOR pos;
	float rotY;
	float startDist;
	int num;
	float interval;
	SpawnerInfo() : timing(0), pos(VZero), rotY(0), startDist(0), num(0), interval(0) {}
};

namespace
{
	SpawnerInfo SGet(const std::string& _type, const float& _timing, const VECTOR& _pos, const float& _rotY = 0,
		const float& _startDist = 0, const int& _num = 1, const float& _interval = 0)
	{
		SpawnerInfo info;
		info.type = _type;
		info.timing = _timing;
		info.pos = _pos;
		info.rotY = _rotY;
		info.startDist = _startDist;
		info.num = _num;
		info.interval = _interval;
		return info;
	}
}

class EnemyManager;

class EnemySpawner
{
public:
	EnemySpawner(const std::unordered_map<std::string, std::function<bool()>>& _conditions, const SpawnerInfo& _info, EnemyManager* _parent);
	~EnemySpawner() {}
	void Update(EnemyManager* _parent);

	bool GetFinish() { return finish; }
	void Reset();

private:
	EnemyManager* parent;
	std::unordered_map<std::string, std::function<bool()>> conditions;
	SpawnerInfo info;
	float elapsedTime;
	float timer;
	bool finish;
	int defNum;
};