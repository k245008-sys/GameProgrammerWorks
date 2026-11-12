#pragma once
#include "Object3D.h"

/*
	画面外にいる敵の方向を表示するオブジェクトクラス
	綾部
*/

class EnemyBase;
class Player;

class OffScreenEnemyGuid : public Object3D
{
public:
	OffScreenEnemyGuid(EnemyBase* _target, const int& _hModel);
	~OffScreenEnemyGuid();
	void Update()override;
	void Draw()override;

	EnemyBase* GetTarget() { return target; }

	void SetTarget(EnemyBase* _target) { target = _target; }
	void SetPlayer(Player* _player) { player = _player; }

private:
	EnemyBase* target;
	Player* player;
};