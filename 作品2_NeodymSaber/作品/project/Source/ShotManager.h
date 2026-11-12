#pragma once
#include "../Library/gameObject.h"
#include <list>

class Object3D;
class Shot_Straight;
class StageManager;
class EnemyManager;
class Player;

class ShotManager : public GameObject
{
public:
	ShotManager();
	~ShotManager();
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;

	void Fire(const VECTOR& _pos, const VECTOR& _rot, const float& _speed);

private:
	bool LineCollisionForShotIterator(std::list<Shot_Straight*>::iterator _it,
		Object3D* _target, const float& _collLength);
	void WallCollision();
	void PlayerCollision();

	std::list<Shot_Straight*> shots;
	StageManager* stageManager;
	EnemyManager* enemyManager;
	Player* player;
};