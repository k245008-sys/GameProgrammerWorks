#include "PlayerState_Attack.h"
#include "EnemyManager.h"
#include "Player.h"
#include "PlayerValue.h"
#include "CommonFunc_PlayerState.h"
#include "Sword_Throw.h"
#include "ScoreManager.h"
#include "InputManager.h"
#include "SoundValue.h"
#include "EffectManager.h"
#include "EffectValue.h"
#include "SoundManager.h"
#include <string>
#include "playScene.h"
#include "Util.h"
#include "VibrationValue.h"

PlayerState_Attack::PlayerState_Attack()
{
	playedSounds.insert({ "Swing", false });
	playedSounds.insert({ "Hit", false });
	playedSounds.insert({ "Voice", false });

	enemyManager = nullptr;
	targetEnemy = nullptr;
	isAttackOver = false;
	isPlusAttackOver = false;
	isNextAttack = false;
	isNextAttract = false;
	enableNextAttackTime = 0;
	atkComboNum = 0;
	direction = VZero;
	attractInputTime = 0;
}

void PlayerState_Attack::Update()
{
	camera->RotationCamera();

	CommonFunc_PlayerState psFunc;
	if (psFunc.JudgeAvoid(this))
		return;
	if (psFunc.JudgeAttractInput(this))
	{
		isNextAttract = true;
		isNextAttack = false;
	}
	else
	{
		isNextAttract = false;
		if (psFunc.JudgeAttackInputDown(this))
		{
			isNextAttack = true;
			enableNextAttackTime = PLAYER_ATTACK_ENABLE_NEXT_ATTACK_DURATION;
		}
	}
	if (isNextAttack)
		enableNextAttackTime -= Time::GameDeltaTime();
	if (enableNextAttackTime <= 0)
		isNextAttack = false;

	Sword_Throw* sw_throw = parent->GetSword_Throw();

	if (psFunc.JudgeThrowOrSnapInputDown(this))
	{
		sw_throw->BeThrown(true);
		psFunc.JudgeSnap(this);
	}

	if (elapsedTime == 0)
	{
		float stickAngle = parent->GetRot().y;
		if (input->IsStickTilt("L"))
		{
			using namespace Util;
			stickAngle = camera->GetRot().y + input->GetStickAngle("L");
			NormalizeAngle(stickAngle);
		}
		atkComboNum = parent->GetAttackComboNum();
		if (atkComboNum == 0 ||
			targetEnemy == nullptr)
		{
			SetTargetEnemy(stickAngle);
			if (targetEnemy != nullptr)
				direction = VNorm(targetEnemy->GetPos() - parent->GetPos());
			else
				direction = VGet(0, 0, 1) * MGetRotY(stickAngle);
		}
		// òAë±çUåÇâÒêîÇâ¡éZ
		parent->AddAttackComboNum();
		atkComboNum = parent->GetAttackComboNum();

		std::string attackName = "Attack";
		parent->PlayAnim(attackName + std::to_string(atkComboNum));

		// çUåÇï˚å¸
		parent->SetRotY(atan2f(direction.x, direction.z));
		if (targetEnemy != nullptr)
		{
			float diffRotY = stickAngle - parent->GetRot().y;
			using namespace Util;
			NormalizeAngle(diffRotY);
			if (fabsf(diffRotY) > PLAYER_ATTACK_ASSIST_DIFF_ROT_Y)
				diffRotY = PLAYER_ATTACK_ASSIST_DIFF_ROT_Y * GetSign<float>(diffRotY);
			parent->SetRotY(parent->GetRot().y + diffRotY);
		}
		parent->SetVelocityXZ(VGet(0, 0, PLAYER_ATTACK_SPEED[atkComboNum - 1]) * MGetRotY(parent->GetRot().y));
	}
	// çUåÇóLå¯éûä‘
	float startCollFrame = 0;
	float endCollFrame = 0;
	bool attackOver = isAttackOver;
	SetCollFrame(startCollFrame, endCollFrame);
	if (atkComboNum == LARGE)
	{
		AnimSetting atkAnim = PLAYER_ANIM_SETTING_ATTACK[atkComboNum - 1];
		if (elapsedTime >= ((PLAYER_ATTACK_COLL_START_FRAME[2]
			- atkAnim.startFrame) / atkAnim.frameSpeed) / 60)
			attackOver = isPlusAttackOver;
		else
			isPlusAttackOver = false;
	}
	if (elapsedTime >= startCollFrame / 60 &&
		elapsedTime < endCollFrame / 60 &&
		!attackOver)
	{
		ForwardAttackColl();
	}
	if (atkComboNum == 3 && elapsedTime >= PLAYER_ATTACK_THIRD_ENABLE_ATTRACT_TIME &&
		isNextAttract)
	{
		nextStateName = "Attract";
		return;
	}

	if (elapsedTime >= PLAYER_ATTACK_TIME[atkComboNum - 1])
	{
		if (isNextAttack &&
			atkComboNum < PLAYER_ATTACK_COMBO_NUM_MAX)
		{
			ResetElapsedTime();
			End();
			return;
		}
		nextStateName = "Idle";
		isNextAttack = false;
		return;
	}

	bool nextAttackFirst = elapsedTime >= PLAYER_ATTACK_NEXT_TIME_AFTER_FIRST && atkComboNum == 1;
	bool nextAttackSecond = elapsedTime >= PLAYER_ATTACK_NEXT_TIME_AFTER_SECOND && atkComboNum == 2;
	if ((nextAttackFirst || nextAttackSecond) && isNextAttack)
	{
		ResetElapsedTime();
		End();
		return;
	}

	PlaySound_Swing();
	PlaySound_Voice();

	elapsedTime += Time::GameDeltaTime();
	parent->MoveVelocity(PLAYER_ATTACK_REDUCE_SPEED[atkComboNum - 1], VZero);

	if (parent->GetIsAnimFinish())
	{
		int frame = PLAYER_AFTER_ATTACK_BLEND_FRAME[atkComboNum - 1];
		parent->SetAnimBlendFrame("Idle", (float)frame);
		parent->PlayAnim("Idle");
	}
}

void PlayerState_Attack::End()
{
	if (nextStateName != "Idle")
		parent->ResetAnimBlendFrame("Idle");
	if(!isNextAttack)
	parent->SetAttackCoolDown(PLAYER_ATTACK_COOL_DOWN);

	// çUåÇÇòAë±Ç≈Ç´ÇÈâÒêîà»â∫Ç»ÇÁÅAòAë±ì¸óÕë“Çøéûä‘ÇÉZÉbÉg
	if (atkComboNum < PLAYER_ATTACK_COMBO_NUM_MAX)
		parent->SetJudgeContinueAttackTime(PLAYER_ATTACK_JUDGE_CONTINUE_TIME);
	isAttackOver = false;
	isPlusAttackOver = false;
	isNextAttack = false;
	attractInputTime = 0;

	sound->Stop("PlayerVoice_Attack_Small");
	sound->Stop("PlayerVoice_Attack_Medium");
	for (auto& s : playedSounds)
		s.second = false;
}

void PlayerState_Attack::AssignFindObjToField()
{
	enemyManager = FindGameObject<EnemyManager>();
	PlayerStateBase::AssignFindObjToField();
}

void PlayerState_Attack::SetTargetEnemy(const float& _baseRotY)
{
	using namespace Util;
	targetEnemy = nullptr;

	float minDist = 0;
	bool isSetFirst = false;
	for (auto& ene : enemyManager->GetEnemies())
	{
		VECTOR dist = ene->GetPos() - parent->GetPos();
		float distSize = VSize(dist);
		float diffRotY = atan2f(dist.x, dist.z) - _baseRotY;
		NormalizeAngle(diffRotY);
		if (distSize > PLAYER_ATTACK_ENABLE_NEAR_ASSIST_DIST ||
			fabsf(diffRotY) > PLAYER_ATTACK_ENABLE_ASSIST_DIFF_ROT_Y)
			continue;
		if (!isSetFirst)
		{
			isSetFirst = true;
			minDist = distSize;
			targetEnemy = ene;
			continue;
		}
		if (minDist > distSize)
		{
			minDist = distSize;
			targetEnemy = ene;
		}
	}
	if (isSetFirst)
		return;

	if (input->IsStickTiltOrKeyPushDir(false))
	{
		float stickAngle = parent->GetRot().y;
		if (input->IsStickTilt("L"))
		{
			stickAngle = camera->GetRot().y + input->GetStickAngle("L");
			NormalizeAngle(stickAngle);
		}
		if (SetTargetEnemyNearRotY(parent->GetPos(), stickAngle,
			PLAYER_ATTACK_ENABLE_NEAR_ASSIST_DIST))
			return;
	}
}

bool PlayerState_Attack::SetTargetEnemyNearRotY(const VECTOR& _basePos, const float& _baseRotY,
	const float& _enableAssistDist)
{
	float minDiffRotY = 0;
	bool isSetFirst = false;
	for (auto& ene : enemyManager->GetEnemies())
	{
		VECTOR dist = ene->GetPos() - _basePos;
		if (VSize(dist) > _enableAssistDist)
			continue;
		float diffRotY = atan2f(dist.x, dist.z) - _baseRotY;
		using namespace Util;
		NormalizeAngle(diffRotY);
		diffRotY = fabsf(diffRotY);
		if (diffRotY > PLAYER_ATTACK_ENABLE_ASSIST_DIFF_ROT_Y)
			continue;
		if (!isSetFirst)
		{
			isSetFirst = true;
			minDiffRotY = diffRotY;
			targetEnemy = ene;
		}
		if (minDiffRotY > diffRotY)
		{
			minDiffRotY = diffRotY;
			targetEnemy = ene;
		}
	}
	return isSetFirst;
}

void PlayerState_Attack::SetCollFrame(float& _start, float& _end)
{
	AnimSetting atkAnim = PLAYER_ANIM_SETTING_ATTACK[atkComboNum - 1];
	int startIndex = 0;
	int endIndex = 0;
	int max = sizeof(PLAYER_ATTACK_COLL_START_FRAME) / sizeof(PLAYER_ATTACK_COLL_START_FRAME[0]) - 1;
	switch (atkComboNum)
	{
	case 2:
		if (elapsedTime < ((PLAYER_ATTACK_COLL_START_FRAME[2]
			- atkAnim.startFrame) / atkAnim.frameSpeed) / 60)
		{
			startIndex = 1;
			endIndex = 1;
		}
		else
		{
			startIndex = 2;
			endIndex = 2;
		}
		break;
	case 3:
		startIndex = max;
		endIndex = max;
		break;
	default:
		break;
	}
	_start = (PLAYER_ATTACK_COLL_START_FRAME[startIndex]
		- atkAnim.startFrame) / atkAnim.frameSpeed;
	_end = (PLAYER_ATTACK_COLL_END_FRAME[endIndex]
		- atkAnim.startFrame) / atkAnim.frameSpeed;
}

void PlayerState_Attack::ForwardAttackColl()
{
	int collNum = 0;
	for (auto& ene : enemyManager->GetEnemies())
	{
		if (!parent->SwordSlashCapsuleColl(ene->GetDamageCollRoot(), ene->GetDamageCollTip(), ENEMY_COLL_RAD))
		{
			continue;
		}
		else
		{
			collNum++;

			isAttackOver = true;
			isPlusAttackOver = true;
			PlaySound_Hit();
			VECTOR dist = ene->GetPos() - parent->GetPos();
			float diffRotY = atan2f(dist.x, dist.z);
			effect->Create("Hit",
				ene->GetPos() + (EFFECT_HIT_ADJUST_POS * MGetRotY(diffRotY)),
				VGet(0, diffRotY, 0));

			VECTOR velocity = VZero;
			if (atkComboNum == PLAYER_ATTACK_COMBO_NUM_MAX)
				velocity.y = PLAYER_ATTACK_FINISH_KNOCK_BACK_Y;
			int index = atkComboNum - 1;
			int size = (int)(sizeof(PLAYER_ATTACK_KNOCK_BACK_SPEED_Z) / sizeof(PLAYER_ATTACK_KNOCK_BACK_SPEED_Z[0]));
			if (index > size - 1)
				index = size - 1;
			velocity.z = PLAYER_ATTACK_KNOCK_BACK_SPEED_Z[index];
			VECTOR knockBack = velocity * MGetRotY(parent->GetRot().y);
			if (ene->GetHp() <= 1 &&
				atkComboNum < PLAYER_ATTACK_COMBO_NUM_MAX)
				ene->BeDead(knockBack);
			else
				ene->Damage(knockBack);

			if (atkComboNum == 3)
				camera->SetShakeCamera(PLAYER_ATTACK_CAMERA_SHAKE_RANGE[atkComboNum - 1], PLAYER_ATTACK_CAMERA_SHAKE_SPEED[atkComboNum - 1],
					PLAYER_ATTACK_CAMERA_SHAKE_TIME[atkComboNum - 1]);
		}
	}
	if (collNum > 0)
	{
		HitStop(collNum);
		Vibration(collNum);
	}
}

void PlayerState_Attack::HitStop(const int& _collNum)
{
	if (_collNum <= 0)
		return;
	SceneBase* scene = SceneManager::CurrentScene();
	PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
	float time = PLAYER_ATTACK_HIT_STOP_PER_ONE[atkComboNum - 1]
		* _collNum;
	float max = PLAYER_ATTACK_HIT_STOP_MAX[atkComboNum - 1];
	if (time > max)
		time = max;
	pScene->HitStop(time);
}

void PlayerState_Attack::Vibration(const int& _collNum)
{
	if (_collNum <= 0 || !input->GetEnableVib())
		return;
	int vib = VIBRATION_POWER_PLAYER_ATTACK_COLL_PER_ONE[atkComboNum - 1]
		* _collNum;
	int max = VIBRATION_POWER_MAX_PLAYER_ATTACK[atkComboNum - 1];
	if (vib > max)
		vib = max;
	StartJoypadVibration(DX_INPUT_PAD1, vib, VIBRATION_TIME_PLAYER_ATTACK[atkComboNum - 1]);
}

void PlayerState_Attack::PlaySound_Swing()
{
	if (elapsedTime < PLAYER_ATTACK_SWING_SOUND_TIMING[atkComboNum - 1])
		return;
	if (playedSounds["Swing"])
		return;
	playedSounds["Swing"] = true;

	switch (atkComboNum - 1)
	{
	case SMALL:
		sound->Play("PlayerAttackSwing_Small");
		break;
	case MEDIUM:
		sound->Play("PlayerAttackSwing_Medium");
		break;
	case LARGE:
		sound->Play("PlayerAttackSwing_Large");
		break;
	default:
		break;
	}
}

void PlayerState_Attack::PlaySound_Hit()
{
	if (elapsedTime < PLAYER_ATTACK_HIT_SOUND_TIMING[atkComboNum - 1])
		return;
	if (playedSounds["Hit"])
		return;
	playedSounds["Hit"] = true;

	int size = (int)(sizeof(PLAYER_ATTACK_SOUND_PITCH) / sizeof(PLAYER_ATTACK_SOUND_PITCH[0]));
	std::string num = std::to_string(GetRand(size - 1));

	switch (atkComboNum - 1)
	{
	case SMALL:
		sound->Play("PlayerAttackHit_Small" + num);
		break;
	case MEDIUM:
		sound->Play("PlayerAttackHit_Medium" + num);
		break;
	case LARGE:
		sound->Play("PlayerAttackHit_Large" + num);
		break;
	default:
		break;
	}
}

void PlayerState_Attack::PlaySound_Voice()
{
	if (elapsedTime < PLAYER_ATTACK_VOICE_TIMING[atkComboNum - 1])
		return;
	if (playedSounds["Voice"])
		return;
	playedSounds["Voice"] = true;

	switch (atkComboNum - 1)
	{
	case SMALL:
		sound->Play("PlayerVoice_Attack_Small");
		break;		
	case MEDIUM:	
		sound->Play("PlayerVoice_Attack_Medium");
		break;		 
	case LARGE:		 
		sound->Play("PlayerVoice_Attack_Large");
		break;
	default:
		break;
	}
}
