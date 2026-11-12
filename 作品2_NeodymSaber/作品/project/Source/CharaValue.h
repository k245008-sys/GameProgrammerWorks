#pragma once

/*
	プレイヤー・敵共通の定数まとめ
	綾部
*/

namespace
{
	// キャラ描画時のY回転調整
	const float CHARA_ADJUST_DRAW_ROT_Y = DEGREE * 180;

	// 重力
	const float GRAVITY = 0.5f * 60;
	// 落下速度の制限
	const float CHARA_VELOCITY_Y_MIN = -30.0f * 60;
	const float CHARA_ADJUST_LENGTH_OF_RAY_GROUND_IN_AIR = 50.0f;

	const float CHARA_COLL_GROUND_RISE_HEIGHT = 0.05f;
	const float CHARA_ADJUST_COLL_SIZE = 0.1f;

	const float CHARA_SHADOW_COLLISION_SIZE = 5000.0f;
	const float CHARA_SHADOW_ADJUST_Y = 2.0f;
	const float CHARA_SHADOW_DEF_ALPHA_RATE = 0.4f;
}