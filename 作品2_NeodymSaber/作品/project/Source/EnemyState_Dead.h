#pragma once
#include "EnemyStateBase.h"

/*
	HPが無くなってステートクラス
	綾部
*/

class EnemyState_Dead : public EnemyStateBase
{
public:
	EnemyState_Dead() {}
	~EnemyState_Dead() {}
	void Update()override;
	void End()override;
};