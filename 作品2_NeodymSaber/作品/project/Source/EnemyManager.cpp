#include "EnemyManager.h"
#include "Enemy_CloseRange.h"
#include "Enemy_LongRange.h"
#include "Enemy_Bomb.h"
#include "../Library/Time.h"
#include "InputManager.h"
#include "debugScreen.h"
#include "Player.h"
#include "config.h"
#include "ColorValue.h"
#include <assert.h>
#include "EnemySpawner.h"
#include "SoundManager.h"
#include "PlayerValue.h"
#include "ScoreManager.h"
#include "ScoreValue.h"
#include "Util.h"

EnemyManager::EnemyManager()
{
	// 各敵のモデル読み込み
	hModels.insert({ "CloseRange", MV1LoadModel("data/model/enemy_closeRange.mv1") });
	hModels.insert({ "LongRange", MV1LoadModel("data/model/enemy_longRange.mv1") });
	hModels.insert({ "Bomb", MV1LoadModel("data/model/enemy_closeRange.mv1") });
	for (auto& m : hModels)
		assert(m.second > 0);

	// 空アニメーションを種類ごとに用意
	anims.insert({ "CloseRange", new Animator() });
	anims.insert({ "LongRange", new Animator() });
	anims.insert({ "Bomb", new Animator() });
	// 共通アニメーション読み込み
	for (auto& a : anims)
		LoadCommonAnim(a.second);
	// 近距離敵のアニメーション
	anims["CloseRange"]->LoadFile("AttackClose", "data/model/animation/E_Attack_Close.mv1", ENEMY_ANIM_SETTING_ATTACK_CLOSE);
	// 遠距離敵のアニメーション
	anims["LongRange"]->LoadFile("BeforeAim", "data/model/animation/E_Enkyori_Attack1.mv1", ENEMY_ANIM_SETTING_BEFORE_AIM);
	anims["LongRange"]->LoadFile("Aim", "data/model/animation/E_Enkyori_Attack2.mv1", ENEMY_ANIM_SETTING_AIM);
	anims["LongRange"]->LoadFile("Fire", "data/model/animation/E_Enkyori_Attack3.mv1", ENEMY_ANIM_SETTING_FIRE);

	// HPごとのテクスチャ読み込み
	textures.emplace_back(LoadGraph("data/model/Texture/Enemy01_redBaseColor.png"));
	textures.emplace_back(LoadGraph("data/model/Texture/Enemy01_yellowBaseColor.png"));
	textures.emplace_back(LoadGraph("data/model/Texture/En_short_01_Enemy01_BaseColor.png"));
	for (int t = 0; t < textures.size(); t++)
		assert(textures[t] > 0);

	// 初期化
	killNum = 0;
	maxEnemyNum = 0;
	doDisplayStartDist = false;
	doDisplayDamageColl = false;

	// スポーン情報をセット
	SetAllSpawn();
}

EnemyManager::~EnemyManager()
{
	// 動的生成データの初期化
	DynamicDataInit();

	// アニメーション
	for (auto& a : anims)
	{
		if (a.second != nullptr)
			delete a.second;
	}
	anims.clear();

	// モデル
	for (auto& m : hModels)
	{
		if(m.second > 0)
		MV1DeleteModel(m.second);
	}
	hModels.clear();

	// テクスチャ
	for (int t = 0; t < (int)textures.size(); t++)
	{
		if(textures[t] > 0)
		DeleteGraph(textures[t]);
	}
	textures.clear();
}

void EnemyManager::Update()
{
	// 反映前のキル数を保存(このフレームだけ条件に達したか確認するため)
	int prevKill = killNum;

	// スポナー
	for (auto it = spawners.begin(); it != spawners.end();)
	{
		EnemySpawner* spw = (*it);
		spw->Update(this);
		if (spw->GetFinish())
		{
			delete spw;
			spw = nullptr;
			it = spawners.erase(it);
			continue;
		}
		it++;
	}

	// 敵
	for (auto& ene : enemies)
	{
		ene->AssignFindObjToField();
		// 各敵でも使うこのクラスでFindしたポインタを渡す
		ene->SetFind(player, sound);
		ene->Update();
		// ＨＰに合わせてテクスチャをセット
		int t = ene->GetHp() / ENEMY_SWITCH_TEXTURE_HP_PER;
		Util::Clamp<int>(t, 0, (int)textures.size() - 1);
		ene->SetTexture(textures[t]);
	}

	// 次の部屋への開扉条件
	// このフレームだけ条件に達したか確認するためのコピー
	std::vector<bool> open;
	for (int op = 0; op < (int)enableOpen.size(); op++)
		open.emplace_back(GetEnableOpen(op + 1));
	// 倒された敵の処理
	CheckDelete();
	for (int op = 0; op < (int)enableOpen.size(); op++)
	{
		// このフレームで開扉条件に達したら
		if (!open[op] && GetEnableOpen(op + 1))
		{
			player->SetHp(PLAYER_HP_MAX);
			sound->Play("Heal");
		}
	}

	// キー入力で使えるデバッグ
#ifdef _DEBUG
	InputManager* input = SceneManager::CommonScene()->FindGameObject<InputManager>();

	// 動き始める条件の判定を表示切り替え
	if (input->IsKeyPushDown("N"))
		doDisplayStartDist = doDisplayStartDist ? false : true;

	// 被ダメージの当たり判定を表示切り替え
	if (input->IsKeyPushDown(ENEMY_DRAW_COLL_INPUT))
		doDisplayDamageColl = doDisplayDamageColl ? false : true;

	// 敵を全て削除
	if (input->IsKeyPushDown("Semicolon"))
		DeleteAll();

	// 敵を１体ずつ削除
	if (input->IsKeyPushDown("L"))
	{
		for (auto it = enemies.begin(); it != enemies.end();)
		{
			delete (*it);
			(*it) = nullptr;
			it = enemies.erase(it);
			killNum++;
			return;
		}
	}

	// リスタート
	if (input->IsKeyPushDown("K"))
	{
		Restart();
	}
#endif

	// このフレームで全キルを達したか
	if (killNum >= maxEnemyNum && prevKill < maxEnemyNum)
	{
		player->ChangeStateOnce("Clear");

		ScoreManager* score = SceneManager::CommonScene()->FindGameObject<ScoreManager>();
		// スコア用タイムをストップ
		score->SetDoCountTime(false);
		// 最終コンボ数
		int combo = score->GetTotalCombo();
		// スコア ＝　コンボ数 × 1つあたりのスコア ＋ 基準タイム × 経過タイムと基準タイムの割合
		int sc = combo * COMBO_SCORE_BASE + (int)(TIME_SCORE_BASE * (1.0f - (score->GetElapsedTime() / TIME_SCORE_BASE)));
		// ランキングに登録
		score->CalcRanking(sc);
	}
}

void EnemyManager::Draw()
{
	for (auto& ene : enemies)
	{
		ene->Draw();

		// 被ダメージ判定表示
		if (doDisplayDamageColl)
			ene->DrawDamageColl();
	}
}

void EnemyManager::AssignFindObjToField()
{
	player = FindGameObject<Player>();
	sound = SceneManager::CommonScene()->FindGameObject<SoundManager>();
}

bool EnemyManager::GetEnableOpen(const int& _areaNum)
{
	int area = _areaNum + -1; // 指定のブロック番号を要素数にする
	// 配列の範囲外防止
	Util::Clamp(area, 0, (int)enableOpen.size() - 1);
	return enableOpen[area]();
}

void EnemyManager::Create(const std::string& _type, const VECTOR& _pos, const float& _startDist, const float& _rotY, const bool& _doCount)
{
	// 生成数カウント(最初に設定したスポーンの総数を保存するため、動的に生成する際は数えない)
	if (_doCount)
		maxEnemyNum++;

	// 指定アニメーションのクローン(中身は同じ新しい実体)を用意
	Animator* anim = anims[_type]->Clone();
	// 指定された種類の敵を生成
	std::string close = "CloseRange";
	std::string lon = "LongRange";
	std::string bomb = "Bomb";
	if (_type == close)
		enemies.emplace_back(new Enemy_CloseRange(hModels[_type], anim, _pos, _startDist, _type, VGet(0, _rotY, 0)));
	else if (_type == lon)
		enemies.emplace_back(new Enemy_LongRange(hModels[lon], anim, _pos, _startDist, _type, VGet(0, _rotY, 0)));
	else if (_type == bomb)
		enemies.emplace_back(new Enemy_Bomb(hModels[bomb], anim, _pos, _startDist, _type, VGet(0, _rotY, 0)));
}

void EnemyManager::Restart()
{
	// 動的生成データの初期化
	DynamicDataInit();
	// キル数リセット
	killNum = 0;
	// スポーン情報をセット
	SetAllSpawn();
}

void EnemyManager::SetAllSpawn()
{
	// 動き始める条件となるプレイヤーとの距離
	float startDist = ENEMY_DEFAULT_JUDGE_START_DIST_TO_PLAYER;

	maxEnemyNum = 0; // 生成カウント初期化

	// １部屋目
	// １ウェーブ目
	VECTOR c = ENEMY_SPAWN_CENTER_BASE_POS[0]; // 基準となる中心座標
	float r = DEGREE * 180; // 入口の方を向かせるY回転度
	Create("LongRange",	 c + VGet(600, 0, 1500), startDist + 2000, r);
	Create("LongRange",  c + VGet(0, 0, 1600), startDist + 2000, r);
	Create("LongRange",  c + VGet(-600, 0, 1500), startDist + 2000, r);
	Create("CloseRange", c + VGet(150, 0, 1000), startDist + 1700, r);
	Create("CloseRange", c + VGet(-150, 0, 1000), startDist + 1700, r);
	Create("CloseRange", c + VGet(300, 0, 800), startDist + 1500, r);
	Create("CloseRange", c + VGet(-300, 0, 800), startDist + 1500, r);

	// ２ウェーブ目
	int kill = maxEnemyNum - 1; // スポーン条件となるキル数
	Spawn(kill, SGet("LongRange", 0,  c + VGet(1300, 0, -1000)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(1200, 0, -1300)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(1500, 0, -1600)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(1400, 0, -1900)));
	Spawn(kill, SGet("CloseRange", 0, c + VGet(0, 0, -1300)));
	Spawn(kill, SGet("CloseRange", 0, c + VGet(200, 0, -1100)));

	// ３ウェーブ目
	kill = maxEnemyNum - 1;
	Spawn(kill, SGet("LongRange", 0,  c + VGet(-1000, 0, 600)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(-1600, 0, 0)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(-1100, 0, 0)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(-1500, 0, -450)));
	Spawn(kill, SGet("LongRange", 0,  c + VGet(-1500, 0, 450)));
	Spawn(kill, SGet("CloseRange", 0, c + VGet(-1000, 0, 0)));
	Spawn(kill, SGet("CloseRange", 0, c + VGet(-900, 0, 150)));
	Spawn(kill, SGet("CloseRange", 0, c + VGet(-800, 0, 300)));

	// １部屋目の敵を全て倒したかの条件をセット
	std::function<bool()> k1 = [this, current = &killNum, target = maxEnemyNum] {return (*current >= target); };
	enableOpen.emplace_back(k1);

	// １～２部屋目の通路
	// 手前
	kill = maxEnemyNum;
	c = ENEMY_SPAWN_CENTER_BASE_POS[1];
	r = DEGREE * 180;
	float s = 1000.0f; // 動き始める距離条件の調整
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, -3300), r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, -3500), r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c + VGet(100, 0, -3500), r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c + VGet(-100, 0, -3500), r, startDist + s));
	Spawn(kill, SGet("Bomb", 0,		 c + VGet(0, 0, -3700), r, startDist + s));

	// 奥
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, -200), r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c, r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c + VGet(300, 0, 0), r, startDist + s));
	Spawn(kill, SGet("LongRange", 0, c + VGet(-300, 0, 0), r, startDist + s));
	Spawn(kill, SGet("Bomb", 0,		 c + VGet(0, 0, -200), r, startDist + s));

	// １～２部屋目の通路の敵を全て倒したかの条件をセット
	std::function<bool()> k2 = [this, current = &killNum, target = maxEnemyNum] {return (*current >= target); };
	enableOpen.emplace_back(k2);

	// ２部屋目(手前)
	// 集団１
	kill = maxEnemyNum;
	c = ENEMY_SPAWN_CENTER_BASE_POS[2];
	r = DEGREE * -90;
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-3000, 0, 200), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-3000, 0, -200), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-3100, 0, 300), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-3100, 0, -300), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-3000, 0, 300), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-3000, 0, -300), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-2900, 0, 0), r, startDist));

	// 集団２
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-1000, 0, 1000), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(-1000, 0, 800), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-1200, 0, 1100), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-1200, 0, 700), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-800, 0, 1100), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(-800, 0, 700), r, startDist));

	// 集団３
	Spawn(kill, SGet("Bomb", 0,			c + VGet(400, 0, -900), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(400, 0, -700), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(200, 0, -1100), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(200, 0, -500), r, startDist));
	Spawn(kill, SGet("Bomb", 0,			c + VGet(600, 0, -1100), r, startDist));
	Spawn(kill, SGet("CloseRange", 0,	c + VGet(600, 0, -500), r, startDist));

	// ２部屋目(高台)
	// 手前
	c = ENEMY_SPAWN_CENTER_BASE_POS[3];
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, -400), r,	startDist + 1500.0f));
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, 0), r,		startDist + 1500.0f));
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, 400), r,	startDist + 1500.0f));

	// 奥
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, 5000), r, startDist + 1500.0f));
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, 5400), r, startDist + 1500.0f));
	Spawn(kill, SGet("LongRange", 0, c + VGet(0, 0, 5800), r, startDist + 1500.0f));

	// ２部屋目(奥)
	kill = maxEnemyNum;
	c = ENEMY_SPAWN_CENTER_BASE_POS[4];
	r = DEGREE * 180;
	Create("CloseRange", c + VGet(300, 0, -3700), startDist, r);
	Create("CloseRange", c + VGet(-300, 0, -3700), startDist, r);
	Create("CloseRange", c + VGet(150, 0, -3900), startDist, r);
	Create("CloseRange", c + VGet(-150, 0, -3900), startDist, r);
	Create("CloseRange", c + VGet(0, 0, -4100),	startDist, r);

	// ２部屋目の敵を全て倒したかの条件をセット
	std::function<bool()> k3 = [this, current = &killNum, target = maxEnemyNum] {return (*current >= target); };
	enableOpen.emplace_back(k3);

	// ３部屋目
	// 右奥
	c = ENEMY_SPAWN_CENTER_BASE_POS[5];
	VECTOR min = VGet(-8700, 0, 17800); // プレイヤー位置判定の最小座標
	VECTOR max = VGet(1000, 0, 30000); // プレイヤー位置判定の最大座標
	Spawn(min, VGet(1000, 0, 30000), SGet("LongRange", 0, c + VGet(-4500, 0, 2900), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4500, 0, 2600), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4500, 0, 2300), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, 2800), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, 2500), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, 2200), r));

	// 左奥
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4500, 0, -2900), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4500, 0, -2600), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4500, 0, -2300), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, -2800), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, -2500), r));
	Spawn(min, max, SGet("LongRange", 0, c + VGet(-4100, 0, -2200), r));

	// 真ん中手前寄り
	float t = 0.5f; // 出現タイミングのインターバル
	Spawn(min, max, SGet("CloseRange", t * 5, c + VGet(-2300, 0, -1000), r));
	Spawn(min, max, SGet("CloseRange", t * 2, c + VGet(-2000, 0, -900), r));
	Spawn(min, max, SGet("CloseRange", t * 9, c + VGet(-2900, 0, -800), r));
	Spawn(min, max, SGet("CloseRange", t * 6, c + VGet(-3000, 0, -700), r));
	Spawn(min, max, SGet("CloseRange", t * 4, c + VGet(-2100, 0, -600), r));
	Spawn(min, max, SGet("CloseRange", t * 7, c + VGet(-3500, 0, -500), r));
	Spawn(min, max, SGet("CloseRange", t * 1, c + VGet(-1800, 0, -400), r));
	Spawn(min, max, SGet("CloseRange", t * 8, c + VGet(-2500, 0, -300), r));
	Spawn(min, max, SGet("CloseRange", t * 3, c + VGet(-1500, 0, -200), r));

	// 入口付近
	float delay = 10.0f; // 前のスポーンと時間差をつける
	Spawn(min, max, SGet("CloseRange", delay + t * 12,	c + VGet(1500, 0, 0), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 3,	c + VGet(1500, 0, 100), r));
	Spawn(min, max, SGet("CloseRange", delay + t,		c + VGet(1500, 0, 200), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 14,	c + VGet(1500, 0, 300), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 10,	c + VGet(1500, 0, 400), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 8,	c + VGet(1500, 0, 500), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 13,	c + VGet(1500, 0, 600), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 6,	c + VGet(1000, 0, 0), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 5,	c + VGet(1000, 0, 100), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 9,	c + VGet(1000, 0, 200), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 7,	c + VGet(1000, 0, 300), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 11,	c + VGet(1000, 0, 400), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 4,	c + VGet(1000, 0, 500), r));
	Spawn(min, max, SGet("CloseRange", delay + t * 2,	c + VGet(1000, 0, 600), r));
}

void EnemyManager::Spawn(const VECTOR& _minPos, const VECTOR& _maxPos, const SpawnerInfo& _info)
{
	// 生成数カウント
	maxEnemyNum++;
	// プレイヤー座標基準のスポーン条件
	std::unordered_map<std::string, std::function<bool()>> s;
	auto c =[this, pos = _minPos, range = _maxPos]{return JudgeSpawnColl(pos, range); };
	s.insert({ "Coll", c });
	// スポナー作成
	spawners.emplace_back(new EnemySpawner(s, _info, this));
}

void EnemyManager::Spawn(const int& _killNum, const SpawnerInfo& _info)
{
	// 生成数カウント
	maxEnemyNum++;
	// 倒された敵の数基準のスポーン条件
	std::unordered_map<std::string, std::function<bool()>> s;
	auto k = [this, first = killNum, target = _killNum] {return JudgeSpawnKill(first, target); };
	s.insert({ "Kill", k });
	// スポナー作成
	spawners.emplace_back(new EnemySpawner(s, _info, this));
}

void EnemyManager::Delete(EnemyBase* _enemy)
{
	if (_enemy == nullptr)
		return;
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		// 指定したインスタンスなら
		if ((*it) == _enemy)
		{
			delete (*it);
			(*it) = nullptr;
			it = enemies.erase(it);
			killNum++; // キル数カウント
			return;
		}
		it++;
	}
}

void EnemyManager::DeleteAll()
{
	// 全ての敵を削除
	for (auto& e : enemies)
	{
		if (e != nullptr)
			delete e;
	}
	enemies.clear();
	// キル数カウント
	killNum = maxEnemyNum;
}

void EnemyManager::CheckDelete()
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		// 倒されているか
		if ((*it)->GetIsDestroy())
		{
			// 削除
			delete (*it);
			(*it) = nullptr;
			it = enemies.erase(it);

			killNum++;
			sound->Play("EnemyDie");
			continue;
		}
		it++;
	}
}

void EnemyManager::DynamicDataInit()
{
	// 全ての敵
	DeleteAll();

	// 開扉条件
	enableOpen.clear();

	// スポナー
	for (int s = 0; s < (int)spawners.size(); s++)
	{
		if (spawners[s] != nullptr)
			delete spawners[s];
	}
	spawners.clear();
}

bool EnemyManager::JudgeSpawnColl(const VECTOR& _minPos, const VECTOR& _maxPos)
{
	// プレイヤーが指定範囲内に入ったか
	VECTOR pPos = player->GetPos();
	pPos.y = _minPos.y;
	return (pPos <= _maxPos && pPos >= _minPos);
}

bool EnemyManager::JudgeSpawnKill(const int& _firstNum, const int& _targetNum)
{
	// 目標キル数に達したか
	return (killNum - _firstNum >= _targetNum);
}

void EnemyManager::LoadCommonAnim(Animator* _anim)
{
	// 全ての敵で共通のアニメーション読み込み

	// アニメーションフォルダのパス
	std::string animFile = "data/model/animation/";
	// 待機
	_anim->LoadFile("Idle", animFile + "E_Stay.mv1", ENEMY_ANIM_SETTING_IDLE);
	// 移動
	_anim->LoadFile("Move", animFile + "E_Move.mv1", ENEMY_ANIM_SETTING_MOVE);
	// ダメージ
	_anim->LoadFile("Damage1", animFile + "E_Damage1.mv1", ENEMY_ANIM_SETTING_DAMAGE[0]);
	_anim->LoadFile("Damage2", animFile + "E_Damage2.mv1", ENEMY_ANIM_SETTING_DAMAGE[1]);
	_anim->LoadFile("Damage3", animFile + "E_Damage3.mv1", ENEMY_ANIM_SETTING_DAMAGE[2]);
	_anim->LoadFile("Damage4", animFile + "E_Damage4.mv1", ENEMY_ANIM_SETTING_DAMAGE[3]);

	// 各方向スナップ(くっついたままの停止状態も有り)
	_anim->LoadFile("SnapFront", animFile + "E_Hikiyose_Front.mv1", ENEMY_ANIM_SETTING_SNAP_FRONT);
	_anim->LoadFile("SnapFrontStop", animFile + "E_Hikiyose_Front.mv1", ENEMY_ANIM_SETTING_SNAP_FRONT_STOP);
	_anim->LoadFile("SnapBack", animFile + "E_Hikiyose_Back.mv1", ENEMY_ANIM_SETTING_SNAP_BACK);
	_anim->LoadFile("SnapBackStop", animFile + "E_Hikiyose_Back.mv1", ENEMY_ANIM_SETTING_SNAP_BACK_STOP);
	_anim->LoadFile("SnapLeft", animFile + "E_Hikiyose_Right.mv1", ENEMY_ANIM_SETTING_SNAP_LEFT);
	_anim->LoadFile("SnapLeftStop", animFile + "E_Hikiyose_Right.mv1", ENEMY_ANIM_SETTING_SNAP_LEFT_STOP);
	_anim->LoadFile("SnapRight", animFile + "E_Hikiyose_Left.mv1", ENEMY_ANIM_SETTING_SNAP_RIGHT);
	_anim->LoadFile("SnapRightStop", animFile + "E_Hikiyose_Left.mv1", ENEMY_ANIM_SETTING_SNAP_RIGHT_STOP);

	// 引き寄せ攻撃をされたとき用
	_anim->LoadFile("LiftedUp", animFile + "E_GoingUp.mv1", ENEMY_ANIM_SETTING_LIFTED_UP);
	_anim->LoadFile("Dropped", animFile + "E_GoingDown.mv1", ENEMY_ANIM_SETTING_DROPPED);
}
