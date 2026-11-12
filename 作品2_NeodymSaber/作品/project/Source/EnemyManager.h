#pragma once
#include "../Library/gameObject.h"
#include <list>
#include "EnemyBase.h"
#include "EnemyValue.h"
#include <functional>
#include "EnemySpawner.h"
#include <memory>

/*
	全体の敵を管理するクラス
	綾部
*/

class Player;
class SoundManager;

class EnemyManager : public GameObject
{
public:
	EnemyManager();
	~EnemyManager();
	void Update()override;
	void Draw()override;

	void AssignFindObjToField()override;

	std::list<EnemyBase*> GetEnemies() { return enemies; }
	bool GetDoDisplayStartDist() { return doDisplayStartDist; }

	/// <summary>
	// 指定した部屋の次への扉が開けるか
	/// </summary>
	/// <param name="_areaNum">何ブロック目(どの部屋か)</param>
	/// <returns>次の部屋への扉が開けるか</returns>
	bool GetEnableOpen(const int& _areaNum);

	/// <summary>
	/// 敵の生成
	/// </summary>
	/// <param name="_type">敵の種類</param>
	/// <param name="_pos">座標</param>
	/// <param name="_startDist">開始判定となる距離</param>
	/// <param name="_rot">Y回転度</param>
	/// <param name="_doCount">敵最大数カウントをするか</param>
	void Create(const std::string& _type, const VECTOR& _pos, const float& _startDist = 0, const float& _rotY = 0, const bool& _doCount = true);

	// ゲーム開始時の状態にリセット
	void Restart();

private:
	// 全てのスポーン情報をセット
	void SetAllSpawn();
	/// <summary>
	/// スポーン情報をセット(プレイヤー座標が基準)
	/// </summary>
	/// <param name="_minPos">判定の最小座標</param>
	/// <param name="_maxPos">判定の最大座標</param>
	/// <param name="_info">セットするスポーン情報</param>
	void Spawn(const VECTOR& _minPos, const VECTOR& _maxPos, const SpawnerInfo& _info);
	/// <summary>
	/// スポーン情報をセット(倒された敵の数が基準)
	/// </summary>
	/// <param name="_killNum">倒された敵の数</param>
	/// <param name="_info">セットするスポーン情報</param>
	void Spawn(const int& _killNum, const SpawnerInfo& _info);

	// 指定と同じ敵インスタンスを削除
	void Delete(EnemyBase* _enemy);
	// 全ての敵を削除
	void DeleteAll();
	// 削除条件を満たしている敵を消す
	void CheckDelete();
	// 動的に生成したデータの初期化
	void DynamicDataInit();

	/// <summary>
	/// プレイヤー座標基準のスポーン条件
	/// </summary>
	/// <param name="_minPos">判定の最小座標</param>
	/// <param name="_maxPos">判定の最大座標</param>
	/// <returns>スポーン可能か</returns>
	bool JudgeSpawnColl(const VECTOR& _minPos, const VECTOR& _maxPos);
	/// <summary>
	/// 倒された敵の数基準のスポーン条件
	/// </summary>
	/// <param name="_firstNum">この関数を呼んだ時点のキル数</param>
	/// <param name="_targetNum">必要な残りキル数</param>
	/// <returns>目標のキル数に達したか</returns>
	bool JudgeSpawnKill(const int& _firstNum, const int& _targetNum);

	// 全敵で共通のアニメーション読み込み
	void LoadCommonAnim(Animator* _anim);

	std::list<EnemyBase*> enemies; // 管理する敵
	std::unordered_map<std::string, int> hModels; // 各種敵モデル
	std::vector<int> textures; // HPごとに用意するテクスチャ
	std::unordered_map<std::string, Animator*> anims; // 各種の敵に必要なアニメーション
	std::vector<EnemySpawner*> spawners; // スポナー

	std::vector<std::function<bool()>> enableOpen; // 各部屋の次への扉が開く条件

	// 参照先
	Player* player;
	SoundManager* sound;

	int maxEnemyNum; // 敵の最大数
	int killNum; // 倒された敵の数

	bool doDisplayStartDist; // 開始判定距離の範囲表示切り替え
	bool doDisplayDamageColl; // 被ダメージ当たり判定の表示切り替え
};