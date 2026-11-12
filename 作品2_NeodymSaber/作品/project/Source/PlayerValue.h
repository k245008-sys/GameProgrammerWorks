#pragma once
#include "Animator.h"
#include "ColorValue.h"
#include "../Library/gameObject.h"

namespace
{
	// モデルの大きさ
	const float PLAYER_DEFAULT_SCALE = 1.0f;
	// 開始位置
	const VECTOR PLAYER_START_POS = VGet(170.0f, 10.0f, 0);

	// 描画位置の調整
	const VECTOR PLAYER_ADJUST_DRAW_POS = VGet(0, 5.0f, 0);

	// 環境光
	const COLOR_F PLAYER_AMB_COLOR = GetColorF(0.0f, 0.1f, 0.1f, 1.0f);

	// コンボ攻撃の最大連続数
	const int PLAYER_ATTACK_COMBO_NUM_MAX = 3;

	// 最大HP
	const int PLAYER_HP_MAX = 6;

	const float PLAYER_ATTRACT_GAUGE_AMOUNT_MAX = 100.0f;
	const float PLAYER_ATTRACT_GAUGE_RECOVERY = 0.3f;
	const float PLAYER_ATTRACT_COOL_DOWN_GAUGE_ZERO = 0.5f;

	const float PLAYER_SHADOW_SIZE = 600.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// デバッグ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_DEBUG_RUN_SPEED = 40.0f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 当たり判定
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const VECTOR PLAYER_ADJUST_RAY_START_POS_JUDGE_ON_GROUND = VGet(0, 30.0f, 0);
	const float PLAYER_DOWN_COLL_SIZE_ON_GROUND = 5.0f;
	const float PLAYER_DOWN_COLL_SIZE_IN_AIR = 20.0f;
	const VECTOR PLAYER_ADJUST_RAY_START_POS_JUDGE_ON_WALL = VGet(0, 60.0f, 0);
	const float PLAYER_WALL_COLL_SIZE = 0.0f;

	const float PLAYER_COLL_RAD = 60.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// アニメーション
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 本モデル用
	const AnimSetting PLAYER_ANIM_SETTING_IDLE = AGet(true);
	const AnimSetting PLAYER_ANIM_SETTING_RUN = AGet(true);
	const AnimSetting PLAYER_ANIM_SETTING_AVOID = AGet(true, 0, 0, 8);

	const AnimSetting PLAYER_ANIM_SETTING_DAMAGE[]
		= { AGet(false, 0, 0.85f), AGet(false, 0, 0.85f) };
	const AnimSetting PLAYER_ANIM_SETTING_DEAD[]
		= { AGet(false, 0, 1.0f), AGet(false, 0, 1.0f) };

	const AnimSetting PLAYER_ANIM_SETTING_ATTRACT[]
		= { AGet(true), AGet(true)};
	const AnimSetting PLAYER_ANIM_SETTING_SWING_UP[]
		= { AGet(false, 16, 0.5f, 3), AGet(false, 16, 0.5f, 3) };
	const AnimSetting PLAYER_ANIM_SETTING_SWING_DOWN[]
		= { AGet(false, 25, 4.5f, 1), AGet(false, 25, 4.5f, 1) };
	const int PLAYER_AFTER_SWING_DOWN_BLEND_FRAME = 10;

	const AnimSetting PLAYER_ANIM_SETTING_AIM = AGet(true);
	const AnimSetting PLAYER_ANIM_SETTING_THROW = AGet(false, 5, 1.3f, 2);

	const AnimSetting PLAYER_ANIM_SETTING_ATTACK[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { AGet(false, 0.0f, 1.7f, 3), AGet(false, 25.0f, 1.2f, 2), AGet(false, 57.0f, 0.92f, 2) };
	// 攻撃判定タイミング
	const float PLAYER_ATTACK_COLL_START_FRAME[]
		={ 13.0f, 26.0f, 38.0f, 61.0f };
	const float PLAYER_ATTACK_COLL_END_FRAME[]
		= { 17.0f, 30.0f, 42.0f, 63.0f };
	const int PLAYER_AFTER_ATTACK_BLEND_FRAME[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 10,10,15 };

	const AnimSetting PLAYER_ANIM_SETTING_SNAP = AGet(true, 0, 1.2f);

	const AnimSetting PLAYER_ANIM_SETTING_AIR_DOWN = AGet(true, 1, 1.0f, 20.0f);
	const AnimSetting PLAYER_ANIM_SETTING_GROUNDING = AGet(false, 2, 1.0f, 2);

	const AnimSetting PLAYER_ANIM_SETTING_CLEAR = AGet(false, 0, 1.0f, 4.0f);

	// 通常移動速度
	const float PLAYER_RUN_SPEED_MAX = 11.0f * 60;
	const float PLAYER_RUN_SPEED_MIN = 9.0f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// ヒットストップ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_ATTACK_HIT_STOP_PER_ONE[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.005f, 0.015f, 0.02f };
	const float PLAYER_ATTACK_HIT_STOP_MAX[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.01f, 0.025f, 0.07f };
	const float PLAYER_ATTRACT_ATTACK_HIT_STOP_PER_ONE = 0.03f;
	const float PLAYER_ATTRACT_ATTACK_HIT_STOP_MAX = 0.12f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 通常攻撃
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// 全体時間
	const float PLAYER_ATTACK_TIME[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.45f, 0.55f, 0.5f };

	// １撃目中に２撃目へ移れるタイミング
	const float PLAYER_ATTACK_NEXT_TIME_AFTER_FIRST = 0.35f;
	// １撃目中に３撃目へ移れるタイミング
	const float PLAYER_ATTACK_NEXT_TIME_AFTER_SECOND = 0.425f;

	// ３連目の攻撃中に引き寄せへ移行できるまでの時間
	const float PLAYER_ATTACK_THIRD_ENABLE_ATTRACT_TIME = 0.32f;
	// コンボ攻撃を続行するかの入力判定時間(攻撃終了後)
	const float PLAYER_ATTACK_JUDGE_CONTINUE_TIME = 0.1f;
	// クールタイム
	const float PLAYER_ATTACK_COOL_DOWN = 0.65f;
	// 攻撃方向への移動速度
	const float PLAYER_ATTACK_SPEED[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 13.0f * 60, 32.0f * 60, 32.0f * 60 };
	// 攻撃方向への移動速度の減速
	const float PLAYER_ATTACK_REDUCE_SPEED[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.7f * 60, 1.3f * 60, 1.0f * 60 };

	// 与えるノックバックの速度
	const float PLAYER_ATTACK_KNOCK_BACK_SPEED_Z[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 25.0f * 60, 20.0f * 60, 56.0f * 60 };
	const float PLAYER_ATTACK_FINISH_KNOCK_BACK_Y = 14.0f * 60;

	// 次攻撃への予備入力の持続時間
	const float PLAYER_ATTACK_ENABLE_NEXT_ATTACK_DURATION = 0.2f;

	const float PLAYER_ATTACK_SWING_SOUND_TIMING[]
		= { 0.0f, 0.0f, 0.0f, 0.0f };
	const float PLAYER_ATTACK_VOICE_TIMING[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.0f, 0.0f, 0.0f };
	const float PLAYER_ATTACK_HIT_SOUND_TIMING[]
		= { 0.0f, 0.0f, 0.0f, 0.0f };

	const VECTOR PLAYER_ATTACK_CAMERA_SHAKE_RANGE[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { VGet(0.0f, 0, 0.0f), VGet(0.0f, 0, 0.0f), VGet(15.0f, 0, 15.0f) };
	const VECTOR PLAYER_ATTACK_CAMERA_SHAKE_SPEED[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { VGet(1.0f, 0, 1.0f), VGet(2.0f, 0, 2.0f), VGet(12.0f, 0, 12.0f) };
	const float PLAYER_ATTACK_CAMERA_SHAKE_TIME[PLAYER_ATTACK_COMBO_NUM_MAX]
		= { 0.1f, 0.15f, 0.2f };

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 通常攻撃アシスト
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_ATTACK_ASSIST_DIFF_ROT_Y = DEGREE * 15.0f;
	// アシスト有効距離
	const float PLAYER_ATTACK_ENABLE_NEAR_ASSIST_DIST = 1000.0f;
	// アシスト有効角度(カメラの向きと敵の向きの差)
	const float PLAYER_ATTACK_ENABLE_ASSIST_DIFF_ROT_Y = DEGREE * 70.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 回避
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_AVOID_TIME = 0.35f;
	const float PLAYER_AVOID_SPEED = 40.0f * 60;
	const float PLAYER_AVOID_REDUCE_SPEED = 1.0f * 60;
	const float PLAYER_AVOID_COOL_DOWN = 0.88f;

	const float PLAYER_AFTER_AVOID_INVINCIBLE_TIME = 0.1f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 短剣投げ前のエイム構え
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// エイム構えになる長押し入力の時間
	const float PLAYER_AIM_JUDGE_LONG_INPUT_TIME = 0.3f;
	// エイム構え時の移動速度
	const float PLAYER_AIM_RUN_SPEED = 5.0f * 60;
	// 軌道表示の大きさ
	const float PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_RAD = 10.0f;
	const unsigned int PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_DIF_COLOR = GetColor(255, 0, 50);
	const unsigned  int PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_SPC_COLOR = GetColor(255, 255, 255);
	// 軌道表示の透過度
	const unsigned int PLAYER_AIM_TRAJECTORY_DRAW_SPHERE_ALPHA = 110;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 短剣投げ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_ATTACK_THROW_ENABLE_ASSIST_DIST_LEAVE = 1000.0f;
	const float PLAYER_ATTACK_THROW_ENABLE_ASSIST_DIST_CLOSE = 5000.0f;
	const float PLAYER_ATTACK_THROW_ENABLE_ASSIST_ROT_Y = DEGREE * 40.0f;

	// 全体時間
	const float PLAYER_THROW_TIME = 0.5f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// スナップ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	
	// 初速
	const float PLAYER_SNAP_FIRST_SPEED = 0.0f * 60;
	// 加速度
	const float PLAYER_SNAP_ADD_SPEED = 0.9f * 60;
	// 最大速度
	const float PLAYER_SNAP_SPEED_MAX = 250.0f * 60;
	// 近くなった時の速度
	const float PLAYER_SNAP_NEAR_FINISH_SPEED = 800.0f * 60;
	// 近くなったかの距離
	const float PLAYER_SNAP_JUDGE_NEAR_FINISH_DIST = 1250.0f;
	// 既に近かった時、現在の距離から何割を近距離判定の長さとして変えるか
	const float PLAYER_SNAP_JUDGE_NEAR_DIST_RATE_ALREADY_NEAR = 0.9f;
	// 既に近かった時、どれくらいの距離で近距離移動するか
	const float PLAYER_SNAP_JUDGE_FINISH_DIST_ALREADY_NEAR = 600.0f;
	// スナップを終える距離
	const float PLAYER_SNAP_JUDGE_FINISH_DIST = 150.0f;
	
	const float PLAYER_SNAP_CANCEL_TIME = 2.5f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 青剣を使った引き寄せ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_ATTRACT_REDUCE_GAUGE = 0.4f;

	const float PLAYER_ATTRACT_DIST = 1200.0f;
	const float PLAYER_ATTRACT_COLL_THICK = 300.0f;
	const float PLAYER_ATTRACT_HEIGHT = 10.0f;

	const int PLAYER_ATTRACT_DRAW_ALPHA = 40;
	const float PLAYER_ATTRACT_DRAW_Y = 10.0f;
	const unsigned int PLAYER_ATTRACT_DRAW_COLOR = BLUE;

	const float PLAYER_ATTRACT_ENABLE_NEXT_ATTACK_DURATION = 0.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 引き寄せ特殊攻撃
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_ATTRACT_ATTACK_REDUCE_GAUGE = 35.0f;

	const float PLAYER_ATTRACT_ATTACK_SWING_START_TIME = 0.07f;

	const float PLAYER_ATTRACT_ATTACK_UP_Y = 400.0f;
	const float PLAYER_ATTRACT_ATTACK_DOWN_Y = 10.0f;
	const float PLAYER_ATTRACT_ATTACK_SWING_UP_TIME = 0.15f;
	const float PLAYER_ATTRACT_ATTACK_SWING_DOWN_TIME = 0.07f;

	const float PLAYER_ATTRACT_ATTACK_GIVE_DAMAGE_SPEED_Y = 10.0f * 60;
	const float PLAYER_ATTRACT_ATTACK_GIVE_DAMAGE_TIME = 0.8f;
	
	const float PLAYER_ATTRACT_ATTACK_NEXT_ATTRACT_COOL_DOWN = 0.5f;

	const VECTOR PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_RANGE = VGet(7.0f, 30.0f, 0);
	const VECTOR PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_SPEED = VGet(7.0f, 25.0f, 0);
	const float PLAYER_ATTRACT_ATTACK_CAMERA_SHAKE_TIME = 0.25f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// ダメージ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_DAMAGE_REDUCE_SPEED = 0.5f * 60;
	const float PLAYER_DAMAGE_BACK_SPEED_SHOT = 20.0f * 60;
	const float PLAYER_DAMAGE_TIME = 0.5f;
	const float PLAYER_AFTER_DAMAGE_INVINCIBLE_TIME = 0.1f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// クリア
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float PLAYER_CLEAR_TIME = 3.0f;
}