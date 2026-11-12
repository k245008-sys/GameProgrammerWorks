#include "EnemySpawner.h"
#include "EnemyManager.h"

EnemySpawner::EnemySpawner(const std::unordered_map<std::string, std::function<bool()>>& _conditions, const SpawnerInfo& _info, EnemyManager* _parent)
{
	conditions = _conditions;
	info = _info;
	defNum = _info.num;
	parent = _parent;
	Reset();
}

void EnemySpawner::Update(EnemyManager* _parent)
{
	if (finish)
		return;
	for (std::pair<std::string, std::function<bool()>> c : conditions)
	{
		if (c.first == "Coll" &&
			c.second())
		{
			std::function<bool()> f = []()->bool{ return true; };
			std::string type = "Coll";
			std::pair<std::string, std::function<bool()>> p = {type, f};
			c.swap(p);
		}
		if (!c.second())
			return;
	}
	elapsedTime += Time::GameDeltaTime();
	if (elapsedTime < info.timing)
		return;
	timer -= Time::GameDeltaTime();
	if (timer <= 0)
	{
		timer = info.interval;
		parent->Create(info.type, info.pos, info.startDist, info.rotY, false);
		info.num--;
		if (info.num <= 0)
			finish = true;
	}
}

void EnemySpawner::Reset()
{
	timer = 0;
	finish = false;
	elapsedTime = 0;
	info.num = defNum;
}
