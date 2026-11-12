#pragma once
#include "SwordBase.h"
#include "SwordState_Equipped.h"
#include "SwordState_Held.h"
#include "SwordState_Thrown.h"
#include "SwordState_Pierced.h"
#include "SwordState_ComeBack.h"

/*
	投げメインで使う剣クラス
	綾部
*/

class InputManager;
class Camera;
class Player;
class EnemyBase;

class Sword_Throw : public SwordBase
{
public:
	Sword_Throw();
	~Sword_Throw();
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;

	VECTOR GetTargetPos() { return targetPos; }
	EnemyBase* GetTargetEnemy() { return targetEnemy; }
	float GetAttractGaugeAmount() { return attractGaugeAmount; }

	void ReduceAttractGaugeAmount(const float& _reduce);

	void CalcTargetPos();
	void BeThrown(const bool& _isLongInput);

	void SetTargetEnemy();

private:
	InputManager* input;
	Camera* camera;
	Player* player;

	SwordState_Equipped s_equipped;
	SwordState_Held s_held;
	SwordState_Thrown s_thrown;
	SwordState_Pierced s_pierced;
	SwordState_ComeBack s_comeBack;

	EnemyBase* targetEnemy;

	VECTOR targetPos;
	float attractGaugeAmount;
};