#pragma once
#include "Object3D.h"
#include "CharaBase.h"
#include "EnemyValue.h"
#include "ColorValue.h"
#include "CircleObj.h"
#include <string>
#include <memory>

/*
	敵の基底クラス
	綾部
*/

class SoundManager;
class Player;
class Emitter;

class EnemyBase : public CharaBase
{
public:
	EnemyBase(const int& _hModel, Animator* _anim, const VECTOR& _pos, const float& _startDist, const std::string& _typeName, const VECTOR& _rot = VZero);
	virtual ~EnemyBase();
	virtual void Update()override;
	virtual void Draw()override;

	void DrawDamageColl();

	virtual void AssignFindObjToField()override;

	void UpdateAnim()override;

	// ゲッター
	StageManager* GetStageManager() { return stageManager; }
	std::string GetTypeName() { return typeName; }
	int GetHp() { return hp; }
	bool GetIsDestroy() { return isDestroy; }
	VECTOR GetSpawnPos() { return spawnPos; }
	float GetDamageTime() { return damageTime; }
	VECTOR GetSnapPos() { return snapPos; }
	float GetChaseDistLeave() { return chaseDistLeave; }
	float GetFinishDist() { return snapFinishDist; }
	WaitAndSeePattern GetWaitAndSeeChance() { return waitAndSeeChance; }
	float GetWaitAndSeeTime() { return waitAndSeeTime; }
	float GetAfterDamageTime() { return afterDamageTime; }
	float GetAfterSnapTime() { return afterSnapTime; }
	float GetAttackCoolDown() { return attackCoolDown; }
	float GetCollRadius() { return collRadius; }
	bool GetIsAttract() { return isAttract; }
	float GetJudgeStartDistToPlayer() { return startDistToPlayer; }
	COLOR_F GetModelColor() { return modelColor; }
	COLOR_F GetAmbColor() { return ambColor; }
	float GetJudgeBackDistNear() { return judgeBackDistNear; }
	VECTOR GetBeforeSwingPos() { return beforeSwingPos; }
	VECTOR GetReduceKnockBackSpeed() { return reduceKnockBackSpeed; }
	VECTOR GetDamageCollRoot() { return transform.position + ENEMY_ADJUST_COLL_ROOT_POS_FROM_ROOT_POS * MGetRotZXY(transform.rotation); }
	VECTOR GetDamageCollTip() { return transform.position + ENEMY_ADJUST_COLL_TIP_POS_FROM_ROOT_POS * MGetRotZXY(transform.rotation); }
	std::string GetWhatAttracted() { return whatAttracted; }
	// 発射口の座標
	VECTOR GetLaunchPortPos() { return GetFrameWorldPos("clavicle_L") + ENEMY_ADJUST_LAUNCHER_POS * MGetRotZXY(GetFrameWorldRot("clavicle_L")); }

	// セッター
	void SetParentToState(DynamicObjBase* _parent) { stateManager->SetParentToCurrentState(_parent); }
	void SetWaitAndSeeTime(const float& _time) { waitAndSeeTime = _time; }
	void SetIsInvincible(const bool& _isInvincible) { isInvincible = _isInvincible; }
	void SetAfterDamageTime(const float& _time) { afterDamageTime = _time; }
	void SetAfterSnapTime(const float& _time) { afterSnapTime = _time; }
	void SetAttackCoolDown(const float& _coolDown) { attackCoolDown = _coolDown; }
	void SetIsAttract(const bool& _isAttract) { isAttract = _isAttract; }
	void SetWhatAttracted(const std::string& _what) { whatAttracted = _what; }
	void SetSwingPosBeforeMove(const VECTOR& _fixedMovePos) { beforeSwingPos = _fixedMovePos; }
	void SetSnapPos(const VECTOR& _snapPos) { snapPos = _snapPos; }
	void SetReduceKnockBackSpeed(const VECTOR& _speed) { reduceKnockBackSpeed = _speed; }
	void SetInPlayerAimArea(const bool& _inPlayerAimArea) { inPlayerAimArea = _inPlayerAimArea; }
	void SetTexture(const int& _t) { MV1SetTextureGraphHandle(hModel, 0, _t, FALSE); }
	// 共通して使うFindしたポインタをセット
	void SetFind(Player* _player, SoundManager* _sound)
	{
		player = _player;
		sound = _sound;
	}

	// 削除する合図
	void Destroy() { isDestroy = true; }
	// リセット処理
	void Reset() { isDestroy = false; }

	// HPに指定した値を加える
	void AddHp(const int& _add) { hp += _add; }

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="_vel">加えるふっ飛び</param>
	/// <param name="_time">ダメージ状態が続く時間(秒)</param>
	virtual void Damage(const VECTOR& _vel, const float& _time = ENEMY_DAMAGE_DEFAULT_TIME);
	/// <summary>
	/// １フレーム後にダメージ処理を発動させる
	/// </summary>
	/// <param name="_vel">加えるふっ飛び</param>
	/// <param name="_time">ダメージ状態が続く時間(秒)</param>
	void DamageOneFrameLater(const VECTOR& _vel, const float& _time = ENEMY_DAMAGE_DEFAULT_TIME);
	/// <summary>
	/// 破壊前の死亡状態になる
	/// </summary>
	/// <param name="_vel">加えるふっ飛び</param>
	virtual void BeDead(const VECTOR& _vel);
	/// <summary>
	/// スナップ状態にする
	/// </summary>
	/// <param name="_snapPos">目標先になる座標</param>
	/// <param name="_finishDist">終了とする距離</param>
	virtual void Snap(const VECTOR& _snapPos, const float& _finishDist);

	bool IsFrontStageColl(); // 前方にステージ判定があるか
	bool IsBackStageColl(); // 後方にステージ判定があるか

	void ExplosionParts(); // パーツ爆散演出

protected:
	// 初期化
	virtual void Init();

	// 参照用
	SoundManager* sound;
	Player* player;

	CircleObj circle; // 円判定表示

	std::string typeName; // 自分がどの種類の敵か

	COLOR_F modelColor; // モデル自体の色(拡散光)
	COLOR_F ambColor; // 環境光

	int hp; // 体力
	bool isDestroy; // 削除されるか
	bool isInvincible; // 無敵状態か

	float collRadius; // 当たり判定の半径サイズ

	VECTOR spawnPos; // 生成位置
	float startDistToPlayer; // 開始条件になるプレイヤーとの距離

	float damageTime; // ダメージ時間
	bool doDelayDamage; // ダメージ発動を遅らせているか
	VECTOR delayedDamageVel; // 遅延ダメージのふっ飛び
	float delayedDamageTime; // 遅延ダメージの時間
	float afterDamageTime; // ダメージ後の時間

	VECTOR beforeSwingPos; // 叩きつけ攻撃を受ける直前の座標

	bool isAttract; // 引き寄せられているか
	std::string whatAttracted; // 何に引き寄せられているか

	VECTOR snapPos;	// スナップ先の座標
	float snapFinishDist; // スナップを終える距離
	float afterSnapTime; // スナップを終えた後の時間

	float chaseDistLeave; // 追跡する距離(これより遠いか)

	WaitAndSeePattern waitAndSeeChance; // 様子見パターンごとの選ばれる確率
	float waitAndSeeTime; // 様子見の時間

	float attackCoolDown; // 攻撃のクールタイム

	float judgeBackDistNear; // 様子見中、後方移動へ強制移行するかの距離(これより近いか)

	VECTOR reduceKnockBackSpeed; // 受けたふっ飛びの減速
	bool inPlayerAimArea; // プレイヤーエイム時の予測磁力範囲に入っているか

private:
	// 基本要素の初期化
	void BaseInit(const VECTOR& _pos);
	// 指定パーツを放出する
	void ExplosionPartsOne(Emitter* _emitter, const std::string& _type);
};