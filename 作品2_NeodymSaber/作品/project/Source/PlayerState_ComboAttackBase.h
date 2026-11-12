#pragma once
#include "PlayerStateBase.h"
#include "../Library/myDxLib.h"
#include <unordered_map>
#include <string>
#include "CommonFunc_PlayerState.h"

/*
	プレイヤーコンボ攻撃ステートクラス
	綾部
*/

class EnemyManager;
class EnemyBase;

class PlayerState_ComboAttackBase : public PlayerStateBase
{
public:
	PlayerState_ComboAttackBase();
	~PlayerState_ComboAttackBase() {}
	virtual void Update()override;
	virtual void End()override;

	virtual void AssignFindObjToField()override;

protected:
	void CheckNextStateFromInput();

	void SetTargetEnemy(const float& _baseRotY);
	bool SetTargetEnemyNearRotY(const VECTOR& _basePos, const float& _baseRotY, const float& _enableAssistDist);
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

	CommonFunc_PlayerState psFunc;
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
	std::unordered_map<std::string, bool> didPlaySounds;
};