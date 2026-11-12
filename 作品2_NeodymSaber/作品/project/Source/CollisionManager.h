#pragma once
#include "../Library/gameObject.h"


/*
	“–‚½‚è”»’è‚Ìˆ—‚Æ‡”Ô‚ğ‚Ü‚Æ‚ß‚ÄŠÇ—‚·‚éƒNƒ‰ƒX
	ˆ»•”
*/

class Player;
class EnemyManager;

class CollisionManager : public GameObject
{
public:
	CollisionManager();
	~CollisionManager();
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;

private:
	VECTOR CalcExtrusionPos(const VECTOR& _velPos, const VECTOR& _basePos,
		const float& _velCollRad, const float& _baseCollRad);

	Player* player;
	EnemyManager* enemyManager;
};