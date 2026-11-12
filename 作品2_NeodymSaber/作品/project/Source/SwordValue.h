#pragma once

#include "ColorValue.h"
#include "../Library/gameObject.h"

namespace
{
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 各剣共通
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 青剣ルートボーンの名前
	const char* SWORD_SLASH_ROOT_NAME = "sword_blue_grp";
	// 赤剣ルートボーンの名前
	const char* SWORD_THROW_ROOT_NAME = "sword_red_grp";

	// 青剣モデルの大きさ
	const VECTOR SWORD_SLASH_SCALE = VGet(1.0f, 1.0f, 1.0f);
	// 赤剣モデルの大きさ
	const VECTOR SWORD_THROW_SCALE = VGet(1.0f, 1.0f, 1.0f);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 青剣
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// ローカル座標の調整
	const VECTOR SWORD_SLASH_ADJUST_LOCAL_POS = VGet(-7.0f, -45.0f, 3.0f);

	// 当たり判定の基準位置の調整
	const VECTOR SWORD_SLASH_ADJUST_COLL_BASE_POS = VGet(-3.5f, 0, 0);
	// 当たり判定の根元の位置調整
	const VECTOR SWORD_SLASH_ADJUST_COLL_ROOT_POS_FROM_BASE_POS = VGet(0, -30, 0);
	// 当たり判定の先端の位置調整
	const VECTOR SWORD_SLASH_ADJUST_COLL_TIP_POS_FROM_BASE_POS = VGet(0, 110, 0);
	// 当たり判定のサイズ(半径)
	const float SWORD_SLASH_COLL_RAD = 100.0f;
	
	// 当たり判定表示のキー
	const std::string SWORD_SLASH_DRAW_COLL_INPUT = "B";
	// 当たり判定表示の色
	const unsigned int SWORD_SLASH_DRAW_COLL_COLOR = GetColor(0, 0, 255);
	// 当たり判定表示の透明度
	const float SWORD_SLASH_DRAW_COLL_ALPHA_PERCENT = 50.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：磁力の性能
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 磁力有効(刺さっている)時間
	const float SWORD_PIERCED_TIME = 2.0f;
	// 赤剣の磁力範囲
	const float SWORD_PIERCED_ATTRACT_DIST = 800.0f;

	// 赤剣の引き寄せゲージ最大量
	const float SWORD_THROW_ATTRACT_GAUGE_AMOUNT_MAX = 100.0f;
	// 赤剣の引き寄せゲージ回復量
	const float SWORD_THROW_ATTRACT_GAUGE_RECOVERY = 5.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：手で持たれている
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 持たれている位置の調整
	const VECTOR SWORD_THROW_ADJUST_HELD_POS = VGet(-15.0f, -30.0f, 3.0f);
	// 持たれている時のローカル回転の調整
	const VECTOR SWORD_THROW_LOCAL_HELD_ROT = VGet(DEGREE * 180.0f, DEGREE * 90.0f, DEGREE * 0.0f);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：装備状態
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 装備中の位置調整
	const VECTOR SWORD_THROW_ADJUST_EQUIPPED_POS = VGet(20.0f, -10.0f, 5.0f);
	// 装備中の位置調整に掛ける回転の調整
	const VECTOR SWORD_THROW_ADJUST_EQUIPPED_ROT_FOR_POS = VGet(DEGREE * -90, DEGREE * 0, DEGREE * 0);
	// 装備中の回転調整
	const VECTOR SWORD_THROW_ADJUST_EQUIPPED_ROT = VGet(DEGREE * 180, DEGREE * 180, DEGREE * -40);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：刺さっている
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	
	// 刺さる位置の調整
	const float SWORD_THROW_ADJUST_PIERCED_POS_Y = 1.0f;
	// 刺さったときのローカル座標の調整
	const VECTOR SWORD_THROW_ADJUST_PIERCED_LOCAL_POS = VGet(0.0f, -20.0f, 0.0f);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：投げられて飛んでいる
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 投げられた状態でのX回転の調整
	const float SWORD_THROW_ADJUST_ROT_X_THROWN = DEGREE * -90;

	// 飛ぶスピード
	const float SWORD_THROW_SPEED = 45.0f * 60;
	// 落ちるタイミングの距離
	const float SWORD_THROW_JUDGE_FALL_DIST = 1300.0f;
	// 飛んでいける距離の限界
	const float SWORD_THROW_FLY_DIST_LIMIT = 10000.0f;

	// 目標の敵へ攻撃中投げされたときの落ちる距離
	const float SWORD_THROW_ATTACK_THROW_JUDGE_FALL_DIST_FROM_TARGET_ENEMY = 300.0f;
	// 目標の敵がいない攻撃中投げをされたときの落ちるタイミングの距離
	const float SWORD_THROW_ATTACK_THROW_JUDGE_FALL_DIST = 2300.0f;
	
	// 重力による減速度
	const float SWORD_THROW_MINUS_SPEED_Y = 1.0f * 60;
	// 重力による減速度の限界
	const float SWORD_THROW_SPEED_Y_MIN = -50.0f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣：プレイヤーへ戻っている
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	
	// 戻ってくる速度
	const float SWORD_COME_BACK_SPEED = 100.0f * 60;
	// 戻りが終わるプレイヤーとの距離
	const float SWORD_COME_BACK_JUDGE_FINISH_DIST = 100.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 赤剣の磁力範囲の描画
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// ポリゴンの細かさ
	const int SWORD_PIERCED_ATTRACT_DIST_DRAW_DIV_NUM = 64;
	// 拡散光
	const unsigned int SWORD_PIERCED_ATTRACT_DIST_DRAW_DIF_COLOR = GetColor(255, 0, 50);
	// 反射光
	const unsigned int SWORD_PIERCED_ATTRACT_DIST_DRAW_SPC_COLOR = WHITE;
	// 塗りつぶすか
	const bool SWORD_PIERCED_ATTRACT_DIST_DRAW_FILL = true;
	// 透明度
	const int SWORD_PIERCED_ATTRACT_DIST_DRAW_ALPHA = 110;
}