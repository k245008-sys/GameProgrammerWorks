#include "OffScreenEnemyGuidManager.h"
#include "OffScreenEnemyGuid.h"
#include "EnemyManager.h"
#include "Player.h"
#include <assert.h>
#include "OffScreenEnemyGuidValue.h"
#include "playScene.h"

OffScreenEnemyGuidManager::OffScreenEnemyGuidManager()
{
	hModel = MV1LoadModel("data/model/offScreenEnemyGuid.mv1");
	assert(hModel > 0);

	enemyManager = nullptr;
	player = nullptr;
	guids.clear();
}

OffScreenEnemyGuidManager::~OffScreenEnemyGuidManager()
{
	if (hModel > 0)
		MV1DeleteModel(hModel);
	guids.clear();
}

void OffScreenEnemyGuidManager::Update()
{
	if (!enable)
		return;

	for (auto guidIt = guids.begin(); guidIt != guids.end();)
	{
		OffScreenEnemyGuid* guid = (*guidIt);
		VECTOR tPos = guid->GetTarget()->GetPos();
		if (CheckCameraViewClip(tPos) == FALSE ||
			VSize(tPos - player->GetPos()) > OFF_SCREEN_ENEMY_GUID_ENABLE_TARGET_DIST)
		{
			guidIt = guids.erase(guidIt);
			continue;
		}
		guidIt++;
	}

	int offScreenEnemyNum = 0;
	for (auto& enemy : enemyManager->GetEnemies())
	{
		bool isOffScreen = (CheckCameraViewClip(enemy->GetPos()) == TRUE &&
			VSize(enemy->GetPos() - player->GetPos()) <= OFF_SCREEN_ENEMY_GUID_ENABLE_TARGET_DIST);
		if (isOffScreen)
			offScreenEnemyNum++;
	}
	for (auto& enemy : enemyManager->GetEnemies())
	{
		bool isOffScreen = (CheckCameraViewClip(enemy->GetPos()) == TRUE &&
			VSize(enemy->GetPos() - player->GetPos()) <= OFF_SCREEN_ENEMY_GUID_ENABLE_TARGET_DIST);
		if (!isOffScreen)
			continue;
		bool isNext = false;
		for (auto& guid : guids)
		{
			if (guid->GetTarget() == enemy)
			{
				isNext = true;
				break;
			}
		}
		if (isNext)
			continue;
		if (guids.size() < offScreenEnemyNum)
		{
			guids.emplace_back(new OffScreenEnemyGuid(enemy, hModel));
		}
	}
	for (auto guidIt = guids.begin(); guidIt != guids.end();)
	{
		OffScreenEnemyGuid* guid = (*guidIt);
		bool haveTarget = false;
		for (auto& enemy : enemyManager->GetEnemies())
		{
			if (guid->GetTarget() != enemy)
				continue;
			haveTarget = true;
			guid->SetTarget(enemy);
			guid->SetPlayer(player);
			guid->Update();
		}
		if (!haveTarget)
		{
			guidIt = guids.erase(guidIt);
			continue;
		}
		guidIt++;
	}
}

void OffScreenEnemyGuidManager::Draw()
{
	if (!enable)
		return;

	SceneBase* scene = SceneManager::CurrentScene();
	PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
	if (pScene != nullptr && pScene->GetIsGameOver())
		return;
	for (auto& guid : guids)
		guid->Draw();
}

void OffScreenEnemyGuidManager::AssignFindObjToField()
{
	enemyManager = FindGameObject<EnemyManager>();
	player = FindGameObject<Player>();
}
