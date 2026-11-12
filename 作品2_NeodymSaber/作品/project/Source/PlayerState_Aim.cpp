#include "PlayerState_Aim.h"
#include "Player.h"
#include "PlayerValue.h"
#include "CommonFunc_PlayerState.h"
#include "CommonFunc_SwordState.h"
#include "Camera.h"
#include "Sword_Throw.h"
#include "SwordValue.h"
#include "InputManager.h"
#include "CommonFunc_CollDraw.h"
#include "EnemyManager.h"
#include "debugScreen.h"

void PlayerState_Aim::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnim("Aim");
		Sword_Throw* sw_throw = parent->GetSword_Throw();
		sw_throw->ChangeStateOnce("Held");
	}

	elapsedTime += Time::GameDeltaTime();

	camera->RotationCamera();
	// カメラ方向を向きながら移動
	VECTOR cRot = camera->GetRot();
	cRot.x *= -1;
	parent->SetRot(cRot);
	CommonFunc_PlayerState psFunc;
	psFunc.SetVelocityXZByCameraAndLStick(PLAYER_AIM_RUN_SPEED, this);

	// 投げボタンを離して投げるステートへ
	if (!psFunc.JudgeThrowOrSnapInput(this))
	{
		nextStateName = "Throw";
		Sword_Throw* sw_throw = parent->GetSword_Throw();
		sw_throw->BeThrown(false);
		return;
	}

	if (psFunc.JudgeAvoid(this) || 
		psFunc.JudgeAttract(this) ||
		psFunc.JudgeAttack(this))
		return;

	// キャンセルボタンも同時押しでキャンセル
	if (input->IsPadPushDown("5"))
	{
		nextStateName = "Idle";
	}
}

void PlayerState_Aim::Draw()
{
	Sword_Throw* sw_throw = parent->GetSword_Throw();
	CommonFunc_SwordState swFunc;
	VECTOR swPos = sw_throw->GetPos();
	VECTOR velocity = swFunc.GetThrowVelocity(swPos);
	VECTOR drawPos = swPos;
	MV1_COLL_RESULT_POLY coll = MV1_COLL_RESULT_POLY();
	while (coll.HitFlag == FALSE)
	{
		if (VSize(drawPos - swPos) > SWORD_THROW_FLY_DIST_LIMIT)
			break;

		sw_throw->CalcTargetPos();
		swFunc.JudgeAndDoFall(drawPos, velocity.y, swPos, sw_throw->GetTargetPos(), true);
		coll = swFunc.IsCollStageObj(drawPos, drawPos + velocity * Time::GameDeltaTime());
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_ALPHA);
		DrawSphere3D(drawPos, PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_RAD, 32,
			PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_DIF_COLOR,
			PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_SPC_COLOR, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		drawPos += velocity * Time::GameDeltaTime();
	}
	if (coll.HitFlag == TRUE)
		drawPos = coll.HitPosition;
	CommonFunc_CollDraw collDraw;
	collDraw.AttractRange_Red(drawPos);
	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	for (auto& enemy : enemyManager->GetEnemies())
		enemy->SetInPlayerAimArea(VSize(drawPos - enemy->GetPos()) <= SWORD_PIERCED_ATTRACT_DIST);
}

void PlayerState_Aim::End()
{
	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	for (auto& enemy : enemyManager->GetEnemies())
		enemy->SetInPlayerAimArea(false);
	parent->SetRotX(0);

	Sword_Throw* sw_throw = parent->GetSword_Throw();
	if (sw_throw->GetCurrentStateName() != "Thrown")
		sw_throw->ChangeStateOnce("Equipped");
}
