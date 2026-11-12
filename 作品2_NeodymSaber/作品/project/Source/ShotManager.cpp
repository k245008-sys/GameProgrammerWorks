#include "ShotManager.h"
#include "Shot_Straight.h"
#include "StageManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ShotValue.h"

ShotManager::ShotManager()
{
	stageManager = nullptr;
	enemyManager = nullptr;
	player = nullptr;

	for (int m = 0; m < SHOT_NUM_MAX; m++)
	{
		shots.emplace_back(new Shot_Straight());
	}
}

ShotManager::~ShotManager()
{
	for (auto shot = shots.begin(); shot != shots.end();)
	{
		shot = shots.erase(shot);
		shot++;
	}
	shots.clear();
}

void ShotManager::Update()
{
	PlayerCollision();
	WallCollision();
	for (auto& it : shots)
		it->Update();
}

void ShotManager::Draw()
{
	for (auto& it : shots)
		it->Draw();
}

void ShotManager::AssignFindObjToField()
{
	stageManager = FindGameObject<StageManager>();
	enemyManager = FindGameObject<EnemyManager>();
	player = FindGameObject<Player>();
}

void ShotManager::Fire(const VECTOR& _pos, const VECTOR& _rot, const float& _speed)
{
	for (auto& s : shots)
	{
		if (!s->GetEnable())
		{
			s->EnableOn(_pos, _rot, _speed);
			return;
		}
	}

	(*shots.begin())->EnableOn(_pos, _rot, _speed);
}

bool ShotManager::LineCollisionForShotIterator(std::list<Shot_Straight*>::iterator _it, Object3D* _target, const float& _targetCollRad)
{
	MV1RefreshCollInfo(_target->GetModel());
	Shot_Straight* shot = *_it;
	VECTOR shotPos = shot->GetPos();
	VECTOR shotVel = shot->GetVelocityGameDelta();
	VECTOR velocity = shotVel + VNorm(shotVel) * (SHOT_COLL_RAD + _targetCollRad);
	MV1_COLL_RESULT_POLY result =
		MV1CollCheck_Line(_target->GetModel(), -1, shotPos, shotPos + velocity);
	if (result.HitFlag == TRUE)
		return true;
	return false;
}

void ShotManager::WallCollision()
{
	for (auto shot = shots.begin(); shot != shots.end();)
	{
		if (!(*shot)->GetEnable())
		{
			shot++;
			continue;
		}
		for (auto& stage : stageManager->GetAllObjects())
		{
			if (LineCollisionForShotIterator(shot, stage, 0))
			{
				(*shot)->EnableOff();
				break;
			}
		}
		shot++;
	}
}

void ShotManager::PlayerCollision()
{
	if (player->GetIsInvincible())
		return;
	for (auto it = shots.begin(); it != shots.end();)
	{
		Shot_Straight* shot = *it;
		if (!shot->GetEnable())
		{
			it++;
			continue;
		}

		bool hit = (bool)HitCheck_Sphere_Capsule(player->GetPos(), PLAYER_COLL_RAD,
			shot->GetPos(), shot->GetPos() + shot->GetVelocity() * Time::GameDeltaTime(), SHOT_COLL_RAD);
		if (hit)
		{
			VECTOR dist = player->GetPos() - shot->GetPos();
			player->Damage(VNorm(dist) * PLAYER_DAMAGE_BACK_SPEED_SHOT);
			shot->EnableOff();
		}
		it++;
	}
}
