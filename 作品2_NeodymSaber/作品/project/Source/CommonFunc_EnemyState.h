#pragma once

#include "EnemyBase.h"
#include <string>

/*
	複数の敵ステートで使う処理まとめ
	綾部
*/

class EnemyStateBase;

class CommonFunc_EnemyState
{
public:
	bool JudgeChase(EnemyStateBase* _eState);
	bool JudgeAttackClose(EnemyStateBase* _eState);
	bool JudgeAim(EnemyStateBase* _eState);
	bool JudgeAttack(EnemyStateBase* _eState);

	void JudgeChaseOrWaitAndSee(EnemyStateBase* _eState);
	void JudgeChaseOrAttackCloseOrWaitAndSee(EnemyStateBase* _eState);
	void JudgeChaseOrAimOrWaitAndSee(EnemyStateBase* _eState);
	void JudgeChaseOrAttackCloseOrAimOrWaitAndSee(EnemyStateBase* _eState);

	void WaitAndSee(EnemyStateBase* _eState);

private:
	float GetPlayerDist(EnemyStateBase* _eState);
};