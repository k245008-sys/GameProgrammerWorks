#pragma once
#include "PlayerStateBase.h"
#include "Camera.h"
#include "Player.h"

#include "PlayerValue.h"
#include "EnemyManager.h"

/*
	複数のプレイヤーステートで使う処理まとめ
	綾部
*/

class CommonFunc_PlayerState
{
public:
	// 攻撃入力
	bool JudgeAttackInput(PlayerStateBase* _pState);
	bool JudgeAttackInputDown(PlayerStateBase* _pState);

	// 剣投げ入力
	bool JudgeThrowOrSnapInput(PlayerStateBase* _pState);
	bool JudgeThrowOrSnapInputDown(PlayerStateBase* _pState);

	// 引き寄せ入力
	bool JudgeAttractInput(PlayerStateBase* _pState);
	bool JudgeAttractInputDown(PlayerStateBase* _pState);

	// 回避入力
	bool JudgeAvoidInputDown(PlayerStateBase* _pState);

	// 攻撃ステート移行
	bool JudgeAttack(PlayerStateBase* _pState);
	// 引き寄せステート移行
	bool JudgeAttract(PlayerStateBase* _pState);
	// 回避ステート移行
	bool JudgeAvoid(PlayerStateBase* _pState);
	// スナップステート移行
	bool JudgeSnap(PlayerStateBase* _pState);
	// 剣投げエイムかスナップ移動ステートへ移行
	bool JudgeAimOrSnap(PlayerStateBase* _pState);

	/// <summary>
	/// 青剣の引き寄せ当たり判定
	/// </summary>
	/// <param name="_dist">対象の座標</param>
	/// <returns>範囲内か</returns>
	bool IsAttractArea(const VECTOR& _pos, PlayerStateBase* _pState);

	// カメラと入力方向からY軸回転を得る
	float GetRotYByCameraAndLStick(PlayerStateBase* _pState);

	// 水平の移動速度をカメラ向きと入力方向からセット
	void SetVelocityXZByCameraAndLStick(const float& _speed, PlayerStateBase* _pState);

	// Y軸回転と水平の移動速度をカメラ向きと入力方向からセット
	void SetRotYAndVelocityXZByCameraAndLStick(const float& _speed, PlayerStateBase* _pState);

	// 青剣の引き寄せ範囲の描画
	void DrawAttractColl(PlayerStateBase* _pState);
};