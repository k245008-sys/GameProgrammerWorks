#pragma once
#include "PlayerStateBase.h"
#include "../Library/myDxLib.h"
#include <unordered_map>
#include <string>

/*
	プレイヤー攻撃ステートクラス
	綾部
*/

class EnemyManager;
class EnemyBase;

class PlayerState_Attack : public PlayerStateBase
{
public:
	PlayerState_Attack();
	~PlayerState_Attack() {}
	void Update()override;
	void End()override;

	void AssignFindObjToField()override;

private:
	void SetTargetEnemy(const float& _baseRotY);
	bool SetTargetEnemyNearRotY(const VECTOR& _basePos, const float& _baseRotY,
		const float& _enableAssistDist);
	void SetCollFrame(float& _start, float& _end);
	void ForwardAttackColl();
	void HitStop(const int& _collNum);
	void Vibration(const int& _collNum);
	void PlaySound_Swing();
	void PlaySound_Hit();
	void PlaySound_Voice();

	enum ATTACK_ID
	{
		SMALL,
		MEDIUM,
		LARGE,
	};

	EnemyManager* enemyManager;
	EnemyBase* targetEnemy;

	bool isAttackOver;
	bool isPlusAttackOver;
	bool isNextAttack;
	bool isNextAttract;
	float enableNextAttackTime;
	int atkComboNum;
	VECTOR direction;
	float attractInputTime;
	std::unordered_map<std::string, bool> playedSounds;
};