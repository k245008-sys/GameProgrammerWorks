#pragma once
#include "ColorValue.h"
#include "../Library/myDxLib.h"
#include "Animator.h"

struct WaitAndSeePattern
{
	float beside;
	float front;
	float back;
	float stay;
	WaitAndSeePattern() : beside(0), front(0), back(0), stay(0) {}
	WaitAndSeePattern(const float& _beside, const float& _front,
		const float& _back, const float& _stay)
	{
		beside = _beside;
		front = _front;
		back = _back;
		stay = _stay;
	}
};

namespace
{
	const int ENEMY_NUM_MAX = 100;
	const float ENEMY_RESPAWN_TIME = 7.0f;

	const float ENEMY_SCALE = 0.9f;

	const int ENEMY_DEFAULT_HP = 5;

	const float ENEMY_DELETE_Y = -500.0f;

	const float ENEMY_SHADOW_SIZE = 700.0f;

	const VECTOR ENEMY_ADJUST_LAUNCHER_POS = VGet(30, 35, -30);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// スポーン設定
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	// スポーンの中心座標の基準(エリアごと)
	const VECTOR ENEMY_SPAWN_CENTER_BASE_POS[]
		= { VGet(150, 300, 5700),		// １部屋目
			VGet(150, 300, 14000),		// １～２部屋目の通路
			VGet(11000, 300, 14000),	// ２部屋目の手前 
			VGet(12600, 800, 14000),	// ２部屋目の高台
			VGet(11000, 300, 22000),	// ２部屋目の奥
			VGet(-2000, 1800, 23000), };// ３部屋目

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// アニメーション
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const AnimSetting ENEMY_ANIM_SETTING_IDLE = AGet(true, 0, 1.0f, 5);
	const AnimSetting ENEMY_ANIM_SETTING_MOVE = AGet(true, 0, 1.0f);

	const AnimSetting ENEMY_ANIM_SETTING_ATTACK_CLOSE = AGet(false, 0, 0.8f, 1);
	const AnimSetting ENEMY_ANIM_SETTING_BEFORE_AIM = AGet(false);
	const AnimSetting ENEMY_ANIM_SETTING_AIM = AGet(true);
	const AnimSetting ENEMY_ANIM_SETTING_FIRE = AGet(false, 73, 1.0f, 1);

	const AnimSetting ENEMY_ANIM_SETTING_DAMAGE[]
		= { AGet(false, 0, 1.5f, 5), AGet(false, 0, 1.5f, 5),
			AGet(false, 0, 1.5f, 5), AGet(false, 0, 1.5f, 5) };

	const AnimSetting ENEMY_ANIM_SETTING_SNAP_FRONT = AGet(true, 0, 1.0f);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_FRONT_STOP = AGet(true, 17, 0, 1);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_BACK = AGet(true, 0, 1.0f);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_BACK_STOP = AGet(true, 34, 0, 1);

	const AnimSetting ENEMY_ANIM_SETTING_SNAP_LEFT = AGet(true, 0, 1.0f);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_LEFT_STOP = AGet(true, 0, 0, 1);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_RIGHT = AGet(true, 0, 1.0f);
	const AnimSetting ENEMY_ANIM_SETTING_SNAP_RIGHT_STOP = AGet(true, 0, 0, 1);

	const float ENEMY_ANIM_SNAP_SIDE_DIFF_ROT = DEGREE * 40;

	const AnimSetting ENEMY_ANIM_SETTING_LIFTED_UP = AGet(false, 0, 1.5f, 1);
	const AnimSetting ENEMY_ANIM_SETTING_DROPPED = AGet(false, 20, 1.5f, 1);

	const float ENEMY_ATTRACTED_AND_FIXED_DROPPED_ANIM_TIMING = 0.18f;

	const float ENEMY_ANIM_AFTER_ATTACK_CLOSE_IDLE_BLEND_FRAME = 40.0f;
	const float ENEMY_ANIM_AFTER_SNAP_IDLE_BLEND_FRAME = 10.0f;
	const float ENEMY_ANIM_AFTER_DAMAGE_IDLE_BLEND_FRAME = 15.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// スポーン
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_SPAWN_TIMING[]
		= { 1.0f, 2.0f, 3.0f };

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 行動開始になる距離
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_DEFAULT_JUDGE_START_DIST_TO_PLAYER = 1500.0f;
	const COLOR_F ENEMY_JUDGE_START_DIST_CIRCLE_DIF_COLOR = GetColorF(0.2f, 0.2f, 0.0f, 0.5f);
	const COLOR_F ENEMY_JUDGE_START_DIST_CIRCLE_AMB_COLOR = GetColorF(0.5f, 0.5f, 0.0f, 1.0f);
	const unsigned int ENEMY_JUDGE_START_DIST_CIRCLE_ALPHA = 20;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// モデルカラー
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const int ENEMY_SWITCH_TEXTURE_HP_PER = 2;

	const COLOR_F ENEMY_DIF_COLOR = GetColorF(0.9f, 0.9f, 0.9f, 1.0f);
	const COLOR_F ENEMY_AMB_COLOR = GetColorF(0.4f, 0.4f, 0.4f, 1.0f);
	const COLOR_F ENEMY_DEAD_COLOR = GetColorF(0.1f, 0.1f, 0.1f, 1.0f);

	const COLOR_F ENEMY_CLOSE_RANGE_COLOR = GetColorF(0.5f, 0.5f, 0.0f, 1.0f);
	const COLOR_F ENEMY_CLOSE_RANGE_AMB_COLOR = GetColorF(0.4f, 0.4f, 0.33f, 1.0f);

	const COLOR_F ENEMY_LONG_RANGE_COLOR = GetColorF(0.7f, 0.3f, 0.7f, 1.0f);
	const COLOR_F ENEMY_LONG_RANGE_AMB_COLOR = GetColorF(0.6f, 0.3f, 0.6f, 1.0f);

	const COLOR_F ENEMY_BOMB_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);
	const COLOR_F ENEMY_BOMB_AMB_COLOR = GetColorF(1.0f, 0.35f, 0.35f, 1.0f);

	const COLOR_F ENEMY_ATTACK_WARNING_COLOR = GetColorF(1.0f, 0.25f, 0.0f, 1.0f);
	const COLOR_F ENEMY_AIM_COLOR = GetColorF(1.0f, 0.0f, 0.4f, 1.0f);
	const COLOR_F ENEMY_IN_ATTRACT_RANGE_COLOR = BLACK_F;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 当たり判定
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const VECTOR ENEMY_ADJUST_RAY_START_POS_JUDGE_ON_GROUND = VGet(0, 30.0f, 0);
	const float ENEMY_DOWN_COLL_SIZE_ON_GROUND = 0.5f;
	const float ENEMY_DOWN_COLL_SIZE_IN_AIR = 0.5f;
	const VECTOR ENEMY_ADJUST_RAY_START_POS_JUDGE_ON_WALL = VGet(0, 50.0f, 0);
	const float ENEMY_WALL_COLL_SIZE = 0.0f;

	const float ENEMY_DEF_COLL_RAD = 30.0f;
	const float ENEMY_CLOSE_RANGE_COLL_RAD = ENEMY_DEF_COLL_RAD;
	const float ENEMY_LONG_RANGE_COLL_RAD = ENEMY_DEF_COLL_RAD;
	const float ENEMY_BOMB_COLL_RAD = ENEMY_DEF_COLL_RAD;

	const VECTOR ENEMY_FRONT_AND_BACK_STAGE_ADJUST_RAY_START_POS = VGet(0, 100.0f, 0);
	const float ENEMY_FRONT_STAGE_COLL_SIZE = 200.0f;
	const float ENEMY_BACK_STAGE_COLL_SIZE = 200.0f;

	// 被ダメージ
	const VECTOR ENEMY_ADJUST_COLL_ROOT_POS_FROM_ROOT_POS = VZero;
	const VECTOR ENEMY_ADJUST_COLL_TIP_POS_FROM_ROOT_POS = VGet(0, 200, 0);
	const float ENEMY_COLL_RAD = 100.0f;

	const std::string ENEMY_DRAW_COLL_INPUT = "E";
	const unsigned int ENEMY_DRAW_COLL_COLOR = GetColor(0, 255, 255);
	const float ENEMY_DRAW_COLL_ALPHA_PERCENT = 50.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// ステート抽選
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const int ENEMY_JUDGE_ATTACK_CHANCE_PERCENT = 80;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 追跡
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_CHASE_vel_ROT_Y_SPEED = DEGREE * 3.0f * 60;

	const float ENEMY_CLOSE_RANGE_JUDGE_CHASE_DIST_LEAVE = 1000.0f;
	const float ENEMY_LONG_RANGE_JUDGE_CHASE_DIST_LEAVE = 3000.0f;
	const float ENEMY_BOMB_JUDGE_CHASE_DIST_LEAVE = 1500.0f;
	const float ENEMY_CHASE_SPEED = 5.0f * 60;
	const float ENEMY_CHASE_vel_VELOCITY_SPEED = 5.0f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 様子見
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_WAIT_AND_SEE_vel_ROT_Y_SPEED = DEGREE * 3.0f * 60;

	const float ENEMY_CLOSE_RANGE_WAIT_AND_SEE_BACK_DIST = 500.0f;
	const float ENEMY_LONG_RANGE_WAIT_AND_SEE_BACK_DIST = 2000.0f;
	const float ENEMY_BOMB_WAIT_AND_SEE_BACK_DIST = 0;

	const WaitAndSeePattern ENEMY_CLOSE_RANGE_WAIT_AND_SEE_CHANCE = { 20, 70, 5, 5 };
	const WaitAndSeePattern ENEMY_LONG_RANGE_WAIT_AND_SEE_CHANCE = { 10, 0, 40, 50 };
	const WaitAndSeePattern ENEMY_BOMB_WAIT_AND_SEE_CHANCE = { 20, 80, 0, 0 };

	const int ENEMY_WAIT_AND_SEE_TIME_RAND_DIGIT_NUM = 1;
	const float ENEMY_WAIT_AND_SEE_TIME_RAND_MIN = 3.0f;
	const float ENEMY_WAIT_AND_SEE_TIME_RAND_MAX = 5.0f;

	const float ENEMY_WAIT_AND_SEE_CHANGE_vel_DIR_INTERVAL = 3.0f;
	const WaitAndSeePattern ENEMY_WAIT_AND_SEE_vel_SPEED = { 2.0f * 60, 2.0f * 60, 2.0f * 60, 0 };

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// エイム
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_AIM_vel_ROT_Y_SPEED = DEGREE * 3.0f * 60;

	const float ENEMY_JUDGE_AIM_DIST_CLOSE = 3000.0f;
	const float ENEMY_JUDGE_AIM_DIST_LEAVE = 1000.0f;
	const float ENEMY_AIM_TIME = 3.5f;
	const float ENEMY_AIM_APPEAR_TRAJECTORY_TIMING = 0.5f;
	const float ENEMY_AIM_WARNING_APPEAR_TIME = 0.25f;
	const float ENEMY_AIM_WARNING_INTERVAL = 0.25f;
	const float ENEMY_AIM_WARNING_TIME = (ENEMY_AIM_WARNING_APPEAR_TIME + ENEMY_AIM_WARNING_INTERVAL) * 2 + 0.2f;

	const float ENEMY_AIM_ADJUST_TARGET_Y = 100.0f;

	const float ENEMY_AIM_TRAJECTORY_RAD = 7.0f;
	const int ENEMY_AIM_TRAJECTORY_DIV_NUM = 16;
	const unsigned int ENEMY_AIM_TRAJECTORY_DIF_COLOR = GetColor(255, 50, 50);
	const unsigned int ENEMY_AIM_TRAJECTORY_SPC_COLOR = WHITE;
	const bool ENEMY_AIM_TRAJECTORY_FILL = true;
	const int ENEMY_AIM_TRAJECTORY_ALPHA = 170;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 発射
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_FIRE_TIME = 3.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 近距離攻撃
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_ATTACK_COOL_DOWN = 5.0f;
	const float ENEMY_JUDGE_ATTACK_DIST_CLOSE = 500.0f;

	const float ENEMY_ATTACK_vel_ROT_Y_SPEED = DEGREE * 3.0f * 60;

	const float ENEMY_BEFORE_ATTACK_TIME = 1.0f;
	const float ENEMY_BEFORE_ATTACK_BLINKING_TIME = 0.2f;
	const float ENEMY_ATTACK_FORWARD_TIME = 0.35f;
	const float ENEMY_ATTACK_FORWARD_SPEED = 27.0f * 60;

	const float ENEMY_ATTACK_COLL_TIMING_START = ENEMY_BEFORE_ATTACK_TIME + 0.1f;
	const float ENEMY_ATTACK_COLL_TIMING_END = ENEMY_ATTACK_COLL_TIMING_START + 0.4f;
	const VECTOR ENEMY_ATTACK_COLL_POS_FROM_ENEMY_POS = VZero;
	const float ENEMY_ATTACK_COLL_DIST = 150.0f;
	const float ENEMY_ATTACK_KNOCK_BACK_SPEED = 30.0f * 60;

	const VECTOR ENEMY_ATTACK_DRAW_WARNING_SIZE = VGet(100.0f, 7.0f, 0);
	const unsigned int ENEMY_ATTACK_DRAW_WARNING_COLOR = GetColor(255, 0, 0);
	const int ENEMY_ATTACK_DRAW_WARNING_ALPHA = 80;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// ダメージ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_DAMAGE_DEFAULT_TIME = 0.35f;
	const float ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Z = 0.78f * 60;
	const float ENEMY_DAMAGE_REDUCE_KNOCK_BACK_SPEED_Y = 0.35f * 60;
	const float ENEMY_AFTER_DAMAGE_TIME = 0.0f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// スナップ
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_SNAP_vel_ROT_Y_SPEED = DEGREE * 10.0f * 60;

	// 初速
	const float ENEMY_SNAP_FIRST_SPEED = 0.0f * 60;
	// 加速度
	const float ENEMY_SNAP_ADD_SPEED = 0.6f * 60;
	// 最大速度
	const float ENEMY_SNAP_SPEED_MAX = 1000.0f * 60;
	// 近くなった時の速度
	const float ENEMY_SNAP_NEAR_FINISH_SPEED = 1000.0f * 60;
	// 近くなったかの距離
	const float ENEMY_SNAP_JUDGE_NEAR_FINISH_DIST = 800.0f;
	// 既に近かった時、現在の距離から何割を近距離判定の長さとして変えるか
	const float ENEMY_SNAP_JUDGE_NEAR_DIST_RATE_ALREADY_NEAR = 0.98f;
	// 既に近かった時、どれくらいの距離で近距離移動するか
	const float ENEMY_SNAP_JUDGE_FINISH_DIST_ALREADY_NEAR = 400.0f;
	// スナップを終える距離
	const float ENEMY_SNAP_JUDGE_FINISH_DIST_TO_SWORD_SLASH = 150.0f;
	const float ENEMY_SNAP_JUDGE_FINISH_DIST_TO_SWORD_THROW = 100.0f;

	const float ENEMY_AFTER_SNAP_TIME = 0.4f;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 爆破
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_EXPLOSION_DIST = 650.0f;
	const float ENEMY_EXPLOSION_GIVE_KNOCK_BACK_SPEED = 10.0f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 爆散演出
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_EXPLOSION_PARTS_LIFE_TIME = 2.0f;
	const float ENEMY_EXPLOSION_PARTS_FADE_OUT_TIME = 0.5f;

	const VECTOR ENEMY_EXPLOSION_PARTS_ADJUST_POS = VGet(0, 130, 0);

	const VECTOR ENEMY_EXPLOSION_PARTS_VELOCITY_MIN = VGet(10, 10, 10) * 60;
	const VECTOR ENEMY_EXPLOSION_PARTS_VELOCITY_MAX = VGet(20, 15, 20) * 60;
	const VECTOR ENEMY_EXPLOSION_PARTS_REDUCE_VELOCITY = VGet(0.05f, 0.5f, 0.05f) * 60;
	const VECTOR ENEMY_EXPLOSION_PARTS_ROT_SPEED_MIN = VGet(10, 10, 10) * DEGREE * 60;
	const VECTOR ENEMY_EXPLOSION_PARTS_ROT_SPEED_MAX = VGet(20, 20, 20) * DEGREE * 60;

	const COLOR_F ENEMY_EXPLOSION_PARTS_DIF_COLOR = GetColorF(0.05f, 0.05f, 0.05f, 1.0f);
	const COLOR_F ENEMY_EXPLOSION_PARTS_AMB_COLOR = GetColorF(0.05f, 0.05f, 0.05f, 1.0f);

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// HPが無くなって破壊されるまでの状態
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const float ENEMY_DEAD_TIME = 0.62f;
	const float ENEMY_DEAD_REDUCE_KNOCK_BACK_SPEED_Z = 0.6f * 60;
	const float ENEMY_DEAD_REDUCE_KNOCK_BACK_SPEED_Y = 0.5f * 60;

	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	// 振動
	//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	const VECTOR ENEMY_FIRST_SNAP_SHAKE_SPEED = VScale(VGet(6.0f, 0, 6.0f), 60);
	const VECTOR ENEMY_FIRST_SNAP_SHAKE_RANGE = VGet(5.0f, 0, 5.0f);
	const float ENEMY_FIRST_SNAP_SHAKE_TIME = 0.05f;
}