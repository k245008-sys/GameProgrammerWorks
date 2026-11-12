#include "CommonFunc_PlayerState.h"
#include "Sword_Throw.h"
#include "../Library/Time.h"
#include "InputManager.h"
#include "StageManager.h"
#include "EnemyManager.h"
#include "DrawBox3D.h"

bool CommonFunc_PlayerState::JudgeAttackInput(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPush("3") || input->IsPadPush("2"));
}

bool CommonFunc_PlayerState::JudgeAttackInputDown(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPushDown("3") || input->IsPadPushDown("2"));
}

bool CommonFunc_PlayerState::JudgeThrowOrSnapInput(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPush("6"));
}

bool CommonFunc_PlayerState::JudgeThrowOrSnapInputDown(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPushDown("6"));
}

bool CommonFunc_PlayerState::JudgeAttractInput(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPush("5"));
}

bool CommonFunc_PlayerState::JudgeAttractInputDown(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPushDown("5"));
}

bool CommonFunc_PlayerState::JudgeAvoidInputDown(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	return (input->IsPadPushDown("1"));
}

bool CommonFunc_PlayerState::JudgeAttack(PlayerStateBase* _pState)
{
	// クールタイム
	if (_pState->GetParent()->GetAttackCoolDown() > PLAYER_ATTACK_COOL_DOWN)
		return false;

	// 入力があって連撃可能か
	if (JudgeAttackInputDown(_pState) &&
		_pState->GetParent()->GetAttackComboNum() < PLAYER_ATTACK_COMBO_NUM_MAX)
	{
		_pState->SetNextStateName("Attack");
		return true;
	}
	return false;
}

bool CommonFunc_PlayerState::JudgeAttract(PlayerStateBase* _pState)
{
	// 可能ゲージ量か
	if (_pState->GetParent()->GetAttractGaugeAmount() <= 0)
		return false;
	// クールタイム
	if (_pState->GetParent()->GetAttractCoolDown() > 0)
		return false;
	// 入力があって攻撃以外のステートか
	if (JudgeAttractInput(_pState) &&
		_pState->GetParent()->GetCurrentStateName() != "Attack")
	{
		_pState->SetNextStateName("Attract");
		return true;
	}
	return false;
}

bool CommonFunc_PlayerState::JudgeAvoid(PlayerStateBase* _pState)
{
	Player* player = _pState->GetParent();
	// クールタイム
	if (player->GetAvoidCoolDown() > 0)
		return false;
	// 入力があるか
	if (JudgeAvoidInputDown(_pState))
	{
		_pState->SetNextStateName("Avoid");
		return true;
	}
	return false;
}

bool CommonFunc_PlayerState::JudgeSnap(PlayerStateBase* _pState)
{
	Sword_Throw* sw_throw = _pState->GetParent()->GetSword_Throw();
	// 赤剣が刺さっているか
	if (sw_throw->GetCurrentStateName() == "Pierced")
	{
		_pState->SetNextStateName("Snap");
		return true;
	}
	return false;
}

bool CommonFunc_PlayerState::JudgeAimOrSnap(PlayerStateBase* _pState)
{
	// 入力があるか
	if (JudgeThrowOrSnapInputDown(_pState))
	{
		if (!JudgeSnap(_pState) && // スナップ移行判定
			// 赤剣が装備状態か
			_pState->GetParent()->GetSword_Throw()->GetCurrentStateName() == "Equipped")
		{
			_pState->SetNextStateName("Aim");
			return true;
		}
	}
	return false;
}

bool CommonFunc_PlayerState::IsAttractArea(const VECTOR& _pos, PlayerStateBase* _pState)
{
	Player* player = _pState->GetParent();
	VECTOR dist = _pos - player->GetPos();
	// 距離判定
	if (VSize(dist) > PLAYER_ATTRACT_DIST)
		return false;
	// 前方判定
	VECTOR attractDir = VGet(0, 0, PLAYER_ATTRACT_DIST) * MGetRotY(player->GetRot().y);
	attractDir = VNorm(attractDir);
	float dotCos = VDot(VNorm(dist), attractDir);
	float diffRotY = acosf(dotCos);
	if (fabsf(diffRotY) > DEGREE * 90)
		return false;
	// 引き寄せ方向との横距離判定
	float distDot = VDot(dist, attractDir);
	VECTOR targetPos = player->GetPos() + dist;
	VECTOR distAttract = (player->GetPos() + attractDir * distDot) - targetPos;
	if (VSize(distAttract) >= PLAYER_ATTRACT_COLL_THICK)
		return false;
	return true;
}

float CommonFunc_PlayerState::GetRotYByCameraAndLStick(PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	Camera* camera = _pState->GetCamera();
	// カメラ方向を基準にした入力方向角度
	return camera->GetRot().y + input->GetStickOrKeyDirAngle(false);
}

void CommonFunc_PlayerState::SetVelocityXZByCameraAndLStick(const float& _speed, PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	Player* player = _pState->GetParent();

	// カメラ方向を基準にした入力方向角度
	float rotY = GetRotYByCameraAndLStick(_pState);
	// スティック傾きの割合を掛けた速度
	float rate = input->GetStickTiltRate("L");

#ifdef _DEBUG
	if (rate == 0 && input->IsKeyPushDir(false))
		rate = 1.0f;
#endif
	float speed = _speed * rate;
	VECTOR moveVec = VGet(0, 0, speed);
	MATRIX mRot = MGetRotY(rotY);
	moveVec = moveVec * mRot;
	player->SetVelocityXZ(moveVec);
}

void CommonFunc_PlayerState::SetRotYAndVelocityXZByCameraAndLStick(const float& _speed, PlayerStateBase* _pState)
{
	InputManager* input = _pState->GetInput();
	Player* player = _pState->GetParent();

	// カメラ方向を基準にした入力方向角度
	float rotY = GetRotYByCameraAndLStick(_pState);
	if (input->IsStickTiltOrKeyPushDir(false))
		player->SetRotY(rotY);

	SetVelocityXZByCameraAndLStick(_speed, _pState);
}

void CommonFunc_PlayerState::DrawAttractColl(PlayerStateBase* _pState)
{
	DrawBox3D box3D;
	Player* player = _pState->GetParent();
	VECTOR size = VGet(PLAYER_ATTRACT_COLL_THICK, PLAYER_ATTRACT_DRAW_Y, PLAYER_ATTRACT_DIST);
	box3D.DrawFront(player->GetPos(), size, VGet(0, player->GetRot().y, 0),
		PLAYER_ATTRACT_DRAW_COLOR, PLAYER_ATTRACT_DRAW_ALPHA);
}