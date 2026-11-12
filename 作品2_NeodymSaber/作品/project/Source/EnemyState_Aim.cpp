#include "EnemyState_Aim.h"
#include "Player.h"
#include "EnemyBase.h"
#include "StageManager.h"
#include "SoundManager.h"
#include "SoundValue.h"

void EnemyState_Aim::Update()
{
	parent->SetVelocityXZ(VZero);
	VECTOR dist = player->GetPos() - parent->GetPos();
	parent->MoveRotY(ENEMY_AIM_vel_ROT_Y_SPEED, atan2f(dist.x, dist.z));
	if (elapsedTime == 0)
		parent->PlayAnim("BeforeAim");

	elapsedTime += Time::GameDeltaTime();
	if (elapsedTime < ENEMY_AIM_TIME - ENEMY_AIM_WARNING_TIME)
	{
		if (parent->GetIsAnimFinish())
			parent->PlayAnim("Aim");
	}
	else
	{
		if (!isWarning)
		{
			isWarning = true;
			SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
			sound->Play("EnemyAttackWarning");
		}
		float time = ENEMY_AIM_WARNING_APPEAR_TIME + ENEMY_AIM_WARNING_INTERVAL;
		if (elapsedTime < ENEMY_AIM_TIME - ENEMY_AIM_WARNING_TIME + time * 2)
		{
			blinkingTimer += Time::GameDeltaTime();
			if (blinkingTimer >= time)
				blinkingTimer = 0;
		}
	}

	if (elapsedTime >= ENEMY_AIM_TIME)
	{
		nextStateName = "Fire";
	}
}

void EnemyState_Aim::Draw()
{
	if (!isWarning && elapsedTime < ENEMY_AIM_APPEAR_TRAJECTORY_TIMING)
		return;
	unsigned int color = ENEMY_AIM_TRAJECTORY_DIF_COLOR;
	if (blinkingTimer >= ENEMY_AIM_WARNING_INTERVAL)
		color = YELLOW;

	VECTOR startPos = VZero;
	VECTOR endPos = VZero;
	bool isFirstIt = true;
	bool isHit = false;
	float minDist = 0;
	VECTOR setPos = VZero;
	for (auto& stageObj : parent->GetStageManager()->GetAllObjects())
	{
		MV1_COLL_RESULT_POLY result = CollideLineBetweenPlayer(stageObj, -1, &startPos, &endPos);
		if (result.HitFlag == TRUE)
		{
			isHit = true;
			float dist = VSize(result.HitPosition - startPos);
			if (isFirstIt)
			{
				minDist = dist;
				setPos = result.HitPosition;
				isFirstIt = false;
				continue;
			}
			if (minDist > dist)
			{
				minDist = dist;
				setPos = result.HitPosition;
			}
		}
	}
	if (isHit)
	{
		endPos = setPos;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ENEMY_AIM_TRAJECTORY_ALPHA);
	DrawCapsule3D(startPos, endPos, ENEMY_AIM_TRAJECTORY_RAD,
		ENEMY_AIM_TRAJECTORY_DIV_NUM, color,
		ENEMY_AIM_TRAJECTORY_SPC_COLOR, (int)ENEMY_AIM_TRAJECTORY_FILL);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EnemyState_Aim::End()
{
	isWarning = false;
	blinkingTimer = 0;
}

MV1_COLL_RESULT_POLY EnemyState_Aim::CollideLineBetweenPlayer(Object3D* _stageObj, const float& _length, VECTOR* _retStartPos, VECTOR* _retEndPos)
{
	VECTOR startPos = parent->GetLaunchPortPos();
	VECTOR endPos = player->GetPos() + VGet(0, ENEMY_AIM_ADJUST_TARGET_Y, 0);
	if (_length > 0)
		endPos = startPos + (VNorm(endPos - startPos) * _length);
	MV1_COLL_RESULT_POLY result =
		MV1CollCheck_Line(_stageObj->GetModel(), -1, startPos, endPos);

	if (_retStartPos != nullptr)
		*_retStartPos = startPos;
	if (_retEndPos != nullptr)
		*_retEndPos = endPos;
	return result;
}
