#include "PlayerState_AttractAttack.h"
#include "Player.h"
#include "PlayerValue.h"
#include "CommonFunc_PlayerState.h"
#include "EnemyManager.h"
#include "Lerp.h"
#include "EffectManager.h"
#include "EffectValue.h"
#include "InputManager.h"
#include "playScene.h"
#include "SoundManager.h"
#include "VibrationValue.h"

void PlayerState_AttractAttack::Update()
{
	camera->RotationCamera();

	if (isFinish)
	{
		gapTime += Time::GameDeltaTime();
		if (gapTime >= (float)PLAYER_AFTER_SWING_DOWN_BLEND_FRAME / 60)
		{
			if (isNextAttract)
				nextStateName = "Attract";
			else
				nextStateName = "Idle";
		}
		return;
	}

	if (elapsedTime == 0)
	{
		sound->Play("PlayerVoice_AttractAttack");
		parent->PlayAnimRand("SwingUp", PLAYER_ANIM_SETTING_SWING_UP);
		parent->SetVelocityXZ(VZero);
		parent->ReduceAttractGaugeAmount(PLAYER_ATTRACT_ATTACK_REDUCE_GAUGE);
	}
	elapsedTime += Time::GameDeltaTime();
	if (elapsedTime < PLAYER_ATTRACT_ATTACK_SWING_START_TIME)
		return;
	Swing();
	lerpTime += Time::GameDeltaTime();

	EnemyManager* enemyManager = FindGameObject<EnemyManager>();

	int collNum = 0;
	for (auto& enemy : enemyManager->GetEnemies())
	{
		if (enemy->GetCurrentStateName() == "Damage")
			continue;

		CommonFunc_PlayerState psFunc;
		// 青剣の磁力範囲内か
		if (!psFunc.IsAttractArea(enemy->GetPos(), this) &&
			enemy->GetCurrentStateName() != "AttractedAndFixed")
			continue;
		enemy->SetSnapPos(parent->GetPos());
		// 青剣特殊攻撃を受けているか
		if (enemy->GetCurrentStateName() != "AttractedAndFixed")
		{
			enemy->ChangeStateOnce("AttractedAndFixed");
			enemy->SetSwingPosBeforeMove(enemy->GetPos());
			enemy->SetVelocity(VZero);
		}
		// 振り上げ・下げの移動をセット
		VECTOR swingPos = enemy->GetBeforeSwingPos() + VGet(0, height, 0);
		VECTOR swingMove = swingPos - enemy->GetPos();
		swingMove /= Time::GameDeltaTime();
		enemy->MovePosAndStageColl(swingPos);
		// 振り下げが終わったら
		if (isFinish)
		{
			GiveDamage(enemy);
			sound->Play("PlayerAttractAttackHit");
			collNum++;
		}
	}
	if (collNum <= 0)
		return;
	SceneBase* scene = SceneManager::CurrentScene();
	PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
	float time = PLAYER_ATTRACT_ATTACK_HIT_STOP_PER_ONE * collNum;
	if (time > PLAYER_ATTRACT_ATTACK_HIT_STOP_MAX)
		time = PLAYER_ATTRACT_ATTACK_HIT_STOP_MAX;
	pScene->HitStop(time);

	if (input->GetEnableVib())
	{
		int vib = VIBRATION_POWER_PLAYER_ATTRACT_ATTACK_COLL_PER_ONE * collNum;
		if (vib > VIBRATION_POWER_MAX_PLAYER_ATTRACT_ATTACK)
			vib = VIBRATION_POWER_MAX_PLAYER_ATTRACT_ATTACK;
		StartJoypadVibration(DX_INPUT_PAD1, vib, VIBRATION_TIME_PLAYER_ATTRACT_ATTACK);
	}
}

void PlayerState_AttractAttack::Draw()
{
	CommonFunc_PlayerState psFunc;
	psFunc.DrawAttractColl(this);
}

void PlayerState_AttractAttack::End()
{
	state = State::SWING_UP;
	height = 0;
	lerpTime = 0;
	isFinish = false;
	gapTime = 0;
	isNextAttract = false;
	parent->ResetAnimBlendFrame("Attract", PLAYER_ANIM_SETTING_ATTRACT);
	parent->ResetAnimBlendFrame("Idle");
}

void PlayerState_AttractAttack::Swing()
{
	isFinish = false;
	switch (state)
	{
	case State::SWING_UP:
		lerpRate = lerpTime / PLAYER_ATTRACT_ATTACK_SWING_UP_TIME;
		lerpRate = EaseOutQuint(lerpRate);
		height = Lerp<float>(0, PLAYER_ATTRACT_ATTACK_UP_Y, lerpRate);
		if (lerpRate >= 1.0f)
		{
			lerpRate = 0;
			lerpTime = 0;
			parent->PlayAnimRand("SwingDown", PLAYER_ANIM_SETTING_SWING_DOWN);
			state = State::SWING_DOWN;
		}
		break;

	case State::SWING_DOWN:
		lerpRate = lerpTime / PLAYER_ATTRACT_ATTACK_SWING_DOWN_TIME;
		lerpRate = EaseInQuint(lerpRate);
		height = Lerp<float>(PLAYER_ATTRACT_ATTACK_UP_Y, PLAYER_ATTRACT_ATTACK_DOWN_Y, lerpRate);
		if (lerpRate >= 1.0f)
		{
			isNextAttract = input->IsPadPush("5");
			if (isNextAttract)
			{
				parent->PlayAnimRand("Attract", PLAYER_ANIM_SETTING_ATTRACT);
				parent->SetAnimBlendFrame(parent->GetPlayAnim(), PLAYER_AFTER_SWING_DOWN_BLEND_FRAME);
			}
			else
			{
				parent->SetAnimBlendFrame("Idle", PLAYER_AFTER_SWING_DOWN_BLEND_FRAME);
				parent->PlayAnim("Idle");
			}
			isFinish = true;
		}
		break;

	default:
		break;
	}
}

void PlayerState_AttractAttack::GiveDamage(EnemyBase* _enemy)
{
	// 振り下げの移動後にダメージ(地面に叩きつけたことを表現するため)
	_enemy->DamageOneFrameLater(VGet(0, PLAYER_ATTRACT_ATTACK_GIVE_DAMAGE_SPEED_Y, 0), PLAYER_ATTRACT_ATTACK_GIVE_DAMAGE_TIME);
	// カメラ振動
	camera->SetShakeCamera(PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_RANGE, PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_SPEED, PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_TIME);
	// エフェクト
	effect->Create("Hit", _enemy->GetPos(), VZero, EFFECT_PLAYER_ATTRACT_ATTACK_HIT_SCALE);
	// 青剣引き寄せのクールタイム
	parent->SetAttractCoolDown(PLAYER_ATTRACT_ATTACK_NEXT_ATTRACT_COOL_DOWN);
}
