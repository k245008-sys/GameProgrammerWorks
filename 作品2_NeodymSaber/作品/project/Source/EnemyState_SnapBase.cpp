#include "EnemyState_SnapBase.h"
#include "EnemyBase.h"
#include "EnemyValue.h"
#include "Player.h"
#include "CommonFunc_EnemyState.h"
#include "Camera.h"
#include "SoundManager.h"
#include "SoundValue.h"
#include "EffectManager.h"
#include "Util.h"

void EnemyState_SnapBase::Update()
{
	using namespace Util;

	// スナップ先と現在位置の距離をセット
	VECTOR dist = parent->GetSnapPos() - parent->GetPos();
	snapMove.SetDistance(dist);

	float toSnapRotY = atan2f(dist.x, dist.z);

	if (elapsedTime == 0)
	{
		float diff = toSnapRotY - parent->GetRot().y;
		NormalizeAngle(diff);

		float range = ENEMY_ANIM_SNAP_SIDE_DIFF_ROT / 2;
		if (diff < DEGREE * -90 + range && diff > DEGREE * -90 - range)
		{
			parent->PlayAnim("SnapLeft");
			dir = "Left";
		}
		else if (diff < DEGREE * 90 + range && diff > DEGREE * 90 - range)
		{
			parent->PlayAnim("SnapRight");
			dir = "Right";
		}
		else if(fabsf(diff) > DEGREE * 90)
		{
			parent->PlayAnim("SnapBack");
			dir = "Back";
		}
		else
		{
			parent->PlayAnim("SnapFront");
			dir = "Front";
		}

		// サウンド
		snapMove.PlaySound_velFirst();
		// 既に近いか判定
		snapMove.SetJudgeNearDist(ENEMY_SNAP_JUDGE_FINISH_DIST_ALREADY_NEAR,
			ENEMY_SNAP_JUDGE_NEAR_FINISH_DIST, ENEMY_SNAP_JUDGE_NEAR_DIST_RATE_ALREADY_NEAR);
		// キャラ振動
		parent->ShakePos(ENEMY_FIRST_SNAP_SHAKE_SPEED, ENEMY_FIRST_SNAP_SHAKE_RANGE,
			ENEMY_FIRST_SNAP_SHAKE_TIME);
	}
	elapsedTime += Time::GameDeltaTime();

	if (dir == "Left")
	{
		toSnapRotY += DEGREE * 90;
		NormalizeAngle(toSnapRotY);
	}
	if (dir == "Right")
	{
		toSnapRotY += DEGREE * -90;
		NormalizeAngle(toSnapRotY);
	}
	if (dir == "Back")
	{
		toSnapRotY += DEGREE * 180;
		NormalizeAngle(toSnapRotY);
	}
	parent->MoveRotY(ENEMY_SNAP_vel_ROT_Y_SPEED, toSnapRotY);

	// スナップの速度まで加速する
	float speed = 0;
	VECTOR snapVel = snapMove.CalcVelocity(speed, ENEMY_SNAP_ADD_SPEED,
		ENEMY_SNAP_SPEED_MAX, ENEMY_SNAP_NEAR_FINISH_SPEED);
	if (speed < ENEMY_SNAP_SPEED_MAX ||
		VSize(snapMove.GetDistance()) > ENEMY_SNAP_JUDGE_NEAR_FINISH_DIST)
		parent->MoveVelocity(speed, snapVel);
	else
		parent->SetVelocity(snapVel);

	if (parent->GetWhatAttracted() != lastWhatAttracted)
	{
		isFirstSnap = false;
		snapMove.ResetFirstUnion();
	}
	lastWhatAttracted = parent->GetWhatAttracted();

	// スナップ終了の判定(くっついているか)
	VECTOR setVel = VZero;
	if (snapMove.JudgeFinishAndGetFinishVel(setVel, parent->GetPos(), parent->GetVelocity(),
		parent->GetSnapPos(), parent->GetFinishDist()))
	{
		// くっついて最初のフレーム
		if (!isFirstSnap)
		{
			isFirstSnap = true;
			parent->SetIsSnap(true);
			parent->SetWasSnap(true);

			parent->SetRotY(toSnapRotY);
			if (dir == "Front")
				parent->PlayAnim("SnapFrontStop");
			if (dir == "Back")
				parent->PlayAnim("SnapBackStop");
			if (dir == "Left")
				parent->PlayAnim("SnapLeftStop");
			if (dir == "Right")
				parent->PlayAnim("SnapRightStop");

			// サウンド
			SoundManager* sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
			sound->Play("SnapUnion2");

			EffectManager* effect = SceneManager::CommonScene()->FindGameObject<EffectManager>();
			VECTOR dist = player->GetPos() - parent->GetPos();
			std::string efType = "SnapUnionRed";

			// 青剣にくっついているか
			if (parent->GetWhatAttracted() == "Slash")
			{
				efType = "SnapUnionBlue";
			}

			// カメラ振動
			Camera* camera = FindGameObject<Camera>();
			camera->SetShakeCamera(CAMERA_SHAKE_RANGE_PLAYER_ATTRACT_SNAP_ENEMY,
				CAMERA_SHAKE_SPEED_PLAYER_ATTRACT_SNAP_ENEMY, CAMERA_SHAKE_TIME_PLAYER_ATTRACT_SNAP_ENEMY);

			effect->Create(efType, parent->GetSnapPos() +
				EFFECT_ADJUST_SNAP_UNION_POS * MGetRotY(atan2f(dist.x, dist.z)),
				VGet(0, atan2f(dist.x, dist.z), 0));
		}
		// くっつき速度をセット
		parent->SetVelocity(setVel);
	}
}

void EnemyState_SnapBase::End()
{
	snapMove.Reset();
	isFirstSnap = false;
	if (parent == nullptr)
		return;
	if (nextStateName == "Idle")
		parent->SetAnimBlendFrame("Idle", ENEMY_ANIM_AFTER_SNAP_IDLE_BLEND_FRAME);
	parent->SetAfterSnapTime(ENEMY_AFTER_SNAP_TIME);
	parent->SetVelocityXZ(VZero);
}
