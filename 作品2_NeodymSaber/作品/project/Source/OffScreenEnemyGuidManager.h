#pragma once
#include "../Library/gameObject.h"
#include <list>

/*
	画面外敵ガイドを管理するクラス
	綾部
*/

class OffScreenEnemyGuid;
class EnemyManager;
class Player;

class OffScreenEnemyGuidManager : public GameObject
{
public:
	OffScreenEnemyGuidManager();
	~OffScreenEnemyGuidManager();
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;
	void SetEnable(const bool& _enable) { enable = _enable; }

private:
	EnemyManager* enemyManager;
	Player* player;
	std::list<OffScreenEnemyGuid*> guids;

	int hModel;
	bool enable;
};