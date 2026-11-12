#pragma once
#include "PlayerStateBase.h"

/*
	プレイヤーの青剣引き寄せ特殊攻撃ステートクラス
	綾部
*/

class EnemyBase;

class PlayerState_AttractAttack : public PlayerStateBase
{
public:
	PlayerState_AttractAttack() : height(0), state(State::SWING_UP), lerpTime(0), lerpRate(0),
		isFinish(false), gapTime(0), isNextAttract(false) {}
	~PlayerState_AttractAttack() {}
	void Update()override;
	void Draw()override;
	void End()override;

private:
	enum class State
	{
		SWING_UP,
		SWING_DOWN,
	};

	void Swing();
	void GiveDamage(EnemyBase* _enemy);

	State state;
	float height;
	float lerpTime;
	float lerpRate;
	bool isFinish;
	float gapTime;
	bool isNextAttract;
};