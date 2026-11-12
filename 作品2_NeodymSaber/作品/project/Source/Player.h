#pragma once
#include "CharaBase.h"

class InputManager;
class EnemyBase;
class SwordBase;
class Sword_Throw;
class Sword_Slash;
class Camera;

/*
	‘€ìƒLƒƒƒ‰‚ÌŠÇ—‚ð‚·‚éƒNƒ‰ƒX
	ˆ»•”
*/

class Player : public CharaBase
{
public:
	Player();
	~Player()override;
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;

	Sword_Throw* GetSword_Throw();
	Sword_Slash* GetSword_Slash();
	int GetAttackComboNum()const { return attackComboNum; }
	float GetJudgeContinueAttackTime()const { return judgeContinueAttackTime; }
	float GetAttackCoolDown()const { return attackCoolDown; }
	float GetAvoidCoolDown()const { return avoidCoolDown; }
	float GetAttractCoolDown()const { return attractCoolDown; }
	float GetAttractGaugeAmount()const { return attractGaugeAmount; }
	int GetHP() { return hp; }
	float GetEnableDebugSpeed()const { return enableDebugSpeed; }
	VECTOR GetLeftHandPos();
	VECTOR GetRightHandPos();
	VECTOR GetLeftHandRot();
	VECTOR GetRightHandRot();
	VECTOR GetHipsPos();
	VECTOR GetHipsRot();
	VECTOR GetDelayedPos() { return delayedPos.front(); }
	bool GetIsInvincible() { return isInvincible; }

	void SetJudgeContinueAttackTime(const float& _judgeTime) { judgeContinueAttackTime = _judgeTime; }
	void SetAttackCoolDown(const float& _coolDown) { attackCoolDown = _coolDown; }
	void SetIsInvincible(const bool& _isInvincible) { isInvincible = _isInvincible; }
	void SetAvoidCoolDown(const float& _coolDown) { avoidCoolDown = _coolDown; }
	void SetAttractCoolDown(const float& _coolDown) { attractCoolDown = _coolDown; }
	void SetHp(const int& _hp) { hp = _hp; }
	void SetInvincibleTime(const float& _time) { invincibleTime = _time; }

	void AddPos(const VECTOR& _add) { transform.position += _add; }
	void AddAttackComboNum() { attackComboNum++; }

	std::string GetPlayAnim() { return anim->GetPlay(); }
	bool GetIsAnimFinish()override;
	void UpdateAnim()override;
	void PlayAnim(const std::string& _name)override;
	template <std::size_t N>
	void PlayAnimRand(const std::string& _name, const AnimSetting(&_setting)[N])
	{
		int max = (int)N;
		int rand = GetRand(max - 1);
		PlayAnim(_name + std::to_string(rand + 1));
	}
	void PlayDamageAnim();
	void SetAnimBlendFrame(const std::string& _name, const float& _blendFrame)override;
	void ResetAnimBlendFrame(const std::string& _name)override;
	template <std::size_t N>
	void ResetAnimBlendFrame(const std::string& _name, const AnimSetting(&_setting)[N])
	{
		for (int a = 0; a < N; a++)
			ResetAnimBlendFrame(_name + std::to_string(a + 1));
	}

	void ReduceAttractGaugeAmount(const float& _reduce);

	void Damage(const VECTOR& _damageVel);

	void DrawDelayedPos();

	bool SwordSlashCapsuleColl(const VECTOR& _start, const VECTOR& _end, const float& _rad);

	void Reset();

private:
	InputManager* input;
	Camera* camera;
	std::vector<SwordBase*> swords;

	int hp;
	bool isInvincible;
	bool debugInvincible;

	int attackComboNum;
	float judgeContinueAttackTime;
	float attackCoolDown;

	std::list<VECTOR> delayedPos;
	float delayedTimer;
	bool enableDelayedPos;

	float avoidCoolDown;
	float invincibleTime;
	float attractCoolDown;
	float attractGaugeAmount;

	bool enableInfiniteAttract;
	bool enableDebugSpeed;
	bool enableAirDownAnim;
};