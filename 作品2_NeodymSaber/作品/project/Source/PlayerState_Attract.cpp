#include "PlayerState_Attract.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayerValue.h"
#include "CommonFunc_PlayerState.h"
#include "InputManager.h"
#include "Sword_Throw.h"

void PlayerState_Attract::Update()
{
	if (elapsedTime == 0)
	{
		parent->PlayAnimRand("Attract", PLAYER_ANIM_SETTING_ATTRACT);
	}
	elapsedTime += Time::GameDeltaTime();

	parent->ReduceAttractGaugeAmount(PLAYER_ATTRACT_REDUCE_GAUGE);

	camera->RotationCamera();

	/*
	if (input->GetEnableVib())
	StartJoypadVibration(DX_INPUT_PAD1, VIBRATION_PLAYER_ATTRACT_POWER, 5);
	*/

	CommonFunc_PlayerState psFunc;
	if (psFunc.JudgeAvoid(this))
		return;
	if (input->IsPadPushDown("4") &&
		parent->GetAttractGaugeAmount() >= PLAYER_ATTRACT_ATTACK_REDUCE_GAUGE &&
		parent->GetIsGround())
	{
		nextStateName = "AttractAttack";
	}

	if (input->IsStickTilt("L"))
	{
		float angle = camera->GetRot().y + input->GetStickAngle("L");
		parent->SetRotY(angle);
	}
	parent->SetVelocityXZ(VZero);

	if (!psFunc.JudgeAttractInput(this) ||
		parent->GetAttractGaugeAmount() <= 0)
	{
		nextStateName = "Idle";
		return;
	}

	EnemyManager* enemyManager = FindGameObject<EnemyManager>();
	bool pierced = parent->GetSword_Throw()->GetCurrentStateName() == "Pierced";
	for (auto& enemy : enemyManager->GetEnemies())
	{
		if (!psFunc.IsAttractArea(enemy->GetPos(), this))
		{
			if (enemy->GetCurrentStateName() == "Snap" && (enemy->GetWhatAttracted() == "Slash" || !pierced))
				enemy->ChangeState("Idle");
			continue;
		}
		enemy->SetWhatAttracted("Slash");
		enemy->Snap(parent->GetPos(), ENEMY_SNAP_JUDGE_FINISH_DIST_TO_SWORD_SLASH);
	}
}

void PlayerState_Attract::Draw()
{
	CommonFunc_PlayerState psFunc;
	psFunc.DrawAttractColl(this);
}

void PlayerState_Attract::End()
{
}
