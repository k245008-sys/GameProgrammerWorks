#include "CommonFunc_EnemyState.h"
#include "EnemyStateBase.h"
#include "Player.h"

bool CommonFunc_EnemyState::JudgeChase(EnemyStateBase* _eState)
{
	if (GetPlayerDist(_eState) > _eState->GetParent()->GetChaseDistLeave())
	{
		_eState->SetNextStateName("Chase");
		return true;
	}
	return false;
}

void CommonFunc_EnemyState::WaitAndSee(EnemyStateBase* _eState)
{
	int randDig = ENEMY_WAIT_AND_SEE_TIME_RAND_DIGIT_NUM;
	int digit = 1;
	while (randDig > 0)
	{
		digit *= 10;
		randDig--;
	}
	float randMin = ENEMY_WAIT_AND_SEE_TIME_RAND_MIN * digit;
	float randMax = ENEMY_WAIT_AND_SEE_TIME_RAND_MAX * digit;
	float randRange = (float)GetRand((int)(randMax - randMin) - 1) + 1;
	float randResult = (randMin + randRange) / digit;
	_eState->GetParent()->SetWaitAndSeeTime(randResult);
	_eState->SetNextStateName("WaitAndSee");
}

bool CommonFunc_EnemyState::JudgeAttackClose(EnemyStateBase* _eState)
{
	if (_eState->GetParent()->GetAfterDamageTime() > 0)
		return false;
	if (_eState->GetParent()->GetAttackCoolDown() <= 0 &&
		GetPlayerDist(_eState) < ENEMY_JUDGE_ATTACK_DIST_CLOSE)
	{
		int rand = GetRand(100 - 1) + 1;
		if (rand > ENEMY_JUDGE_ATTACK_CHANCE_PERCENT)
			return false;
		_eState->SetNextStateName("AttackClose");
		return true;
	}
	return false;
}

bool CommonFunc_EnemyState::JudgeAim(EnemyStateBase* _eState)
{
	if (_eState->GetParent()->GetAfterDamageTime() > 0)
		return false;
	if (_eState->GetParent()->GetAttackCoolDown() <= 0 &&
		GetPlayerDist(_eState) <= ENEMY_JUDGE_AIM_DIST_CLOSE &&
		GetPlayerDist(_eState) >= ENEMY_JUDGE_AIM_DIST_LEAVE)
	{
		int rand = GetRand(100 - 1) + 1;
		if (rand > ENEMY_JUDGE_ATTACK_CHANCE_PERCENT)
			return false;
		_eState->SetNextStateName("Aim");
		return true;
	}
	return false;
}

bool CommonFunc_EnemyState::JudgeAttack(EnemyStateBase* _eState)
{
	if (_eState->GetParent()->GetTypeName() == "CloseRange")
		return JudgeAttackClose(_eState);
	if (_eState->GetParent()->GetTypeName() == "LongRange")
		return JudgeAim(_eState);
	if (_eState->GetParent()->GetTypeName() == "NoSnap")
		return JudgeAim(_eState);
	return false;
}

void CommonFunc_EnemyState::JudgeChaseOrAttackCloseOrWaitAndSee(EnemyStateBase* _eState)
{
	if (JudgeChase(_eState))
		return;
	if (JudgeAttackClose(_eState))
		return;
	WaitAndSee(_eState);
}

void CommonFunc_EnemyState::JudgeChaseOrAimOrWaitAndSee(EnemyStateBase* _eState)
{
	if (JudgeChase(_eState))
		return;
	if (JudgeAim(_eState))
		return;
	WaitAndSee(_eState);
}

void CommonFunc_EnemyState::JudgeChaseOrAttackCloseOrAimOrWaitAndSee(EnemyStateBase* _eState)
{
	if (JudgeChase(_eState))
		return;
	if (JudgeAttackClose(_eState))
		return;
	if (JudgeAim(_eState))
		return;
	WaitAndSee(_eState);
}

void CommonFunc_EnemyState::JudgeChaseOrWaitAndSee(EnemyStateBase* _eState)
{
	if (JudgeChase(_eState))
		return;
	WaitAndSee(_eState);
}


float CommonFunc_EnemyState::GetPlayerDist(EnemyStateBase* _eState)
{
	return VSize(_eState->GetParent()->GetPos()
		- _eState->GetPlayer()->GetPos());
}
