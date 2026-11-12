#include "CollisionManager.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "PlayerValue.h"
#include "EnemyValue.h"
#include "CollisionFunc.h"

CollisionManager::CollisionManager()
{
	player = nullptr;
	enemyManager = nullptr;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	std::list<EnemyBase*> enemies = enemyManager->GetEnemies();
	for (auto baseEne = enemies.begin(); baseEne != enemies.end();)
	{
		EnemyBase* baseEnemy = *baseEne;
		auto comparEne = baseEne;
		comparEne++;
		while (comparEne != enemies.end())
		{
			EnemyBase* comparEnemy = *comparEne;
			baseEnemy->MovePosAndStageColl(CalcExtrusionPos(baseEnemy->GetPos(), comparEnemy->GetPos(),
				baseEnemy->GetCollRadius(), comparEnemy->GetCollRadius()));
			comparEne++;
		}
		baseEnemy->MovePosAndStageColl(CalcExtrusionPos(baseEnemy->GetPos(), player->GetPos(),
			baseEnemy->GetCollRadius(), PLAYER_COLL_RAD));

		baseEne++;
	}
}

void CollisionManager::Draw()
{
}

void CollisionManager::AssignFindObjToField()
{
	player = FindGameObject<Player>();
	enemyManager = FindGameObject<EnemyManager>();
}

VECTOR CollisionManager::CalcExtrusionPos(const VECTOR& _velPos, const VECTOR& _basePos,
	const float& _velCollRad, const float& _baseCollRad)
{
	VECTOR dist = _velPos - _basePos;
	float collSize = _velCollRad + _baseCollRad;
	if (VSize(dist) > collSize)
		return _velPos;

	VECTOR setPos = _velPos + VNorm(dist) * (collSize - VSize(dist));
	setPos.y = _velPos.y;
	return setPos;
}
