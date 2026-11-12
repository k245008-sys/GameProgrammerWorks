#include "CommonFunc_SwordState.h"
#include "SwordValue.h"
#include "SwordBase.h"
#include "StageManager.h"
#include "Player.h"
#include "Camera.h"
#include "MoveNum.h"
#include "Sword_Throw.h"

void CommonFunc_SwordState::JudgeAndDoFall(const VECTOR& _velPos, float& _velocityY, const VECTOR& _firstPos, const VECTOR& _targetPos,
	const bool& _isDraw)
{
	if (!_isDraw)
	{
		Player* player = FindGameObject<Player>();
		Sword_Throw* sw_throw = player->GetSword_Throw();
		if (sw_throw->GetTargetEnemy() != nullptr)
		{
			if (VSize(_targetPos - _velPos) <= SWORD_THROW_ATTACK_THROW_JUDGE_FALL_DIST_FROM_TARGET_ENEMY)
			{
				MoveNum moveNum;
				moveNum.MoveToTarget(_velocityY, SWORD_THROW_MINUS_SPEED_Y, SWORD_THROW_SPEED_Y_MIN);
			}
			return;
		}
	}
	float judgeFallDist = SWORD_THROW_JUDGE_FALL_DIST;
	if (VSize(_targetPos - _firstPos) < SWORD_THROW_JUDGE_FALL_DIST)
		judgeFallDist = 0;
	if (VSize(_velPos - _firstPos) >= judgeFallDist)
	{
		MoveNum moveNum;
		moveNum.MoveToTarget(_velocityY, SWORD_THROW_MINUS_SPEED_Y, SWORD_THROW_SPEED_Y_MIN);
	}
}

MV1_COLL_RESULT_POLY CommonFunc_SwordState::IsCollStageObj(const VECTOR& _startPos, const VECTOR& _endPos)
{
	StageManager* stageManager = FindGameObject<StageManager>();
	MV1_COLL_RESULT_POLY result = MV1_COLL_RESULT_POLY();
	for (auto& it : stageManager->GetAllObjects())
	{
		MV1RefreshCollInfo(it->GetModel());
		result = MV1CollCheck_Line(it->GetModel(), -1, _startPos, _endPos);
		if (result.HitFlag == TRUE)
			return result;
	}
	return result;
}

VECTOR CommonFunc_SwordState::GetThrowVelocity(const VECTOR& _pos)
{
	VECTOR dist = GetDistToThrowTarget(_pos);
	VECTOR toTargetDir = VNorm(dist);
	return toTargetDir * SWORD_THROW_SPEED;
}

VECTOR CommonFunc_SwordState::GetDistToThrowTarget(const VECTOR& _pos)
{
	Player* player = FindGameObject<Player>();
	Camera* camera = FindGameObject<Camera>();
	VECTOR pPos = player->GetPos();
	VECTOR cPos = camera->GetPos();
	VECTOR cTarPos = camera->GetAimTarget();
	VECTOR targetPos = cPos + VNorm(cTarPos - cPos)
		* (VSize(pPos - cPos) + SWORD_THROW_FLY_DIST_LIMIT);
	return targetPos - _pos;
}
