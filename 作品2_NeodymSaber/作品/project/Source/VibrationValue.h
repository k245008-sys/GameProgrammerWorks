#pragma once

/*
	コントローラー振動の調整値まとめ
	綾部
*/

namespace
{
	// １～１０００の強さで振動

	// くっついた時の振動強度
	const int VIBRATION_POWER_SNAP_UNION = 1000;
	// くっついた時の振動時間
	const int VIBRATION_TIME_SNAP_UNION = 200;

	// プレイヤー通常攻撃で当たった敵１体ごとに増える振動強度の値
	const int VIBRATION_POWER_PLAYER_ATTACK_COLL_PER_ONE[]
		= { 200, 300, 400 };
	// プレイヤー通常攻撃での振動強度の最大
	const int VIBRATION_POWER_MAX_PLAYER_ATTACK[]
		= { 300, 500, 800 };
	// プレイヤー通常攻撃での振動時間
	const int VIBRATION_TIME_PLAYER_ATTACK[]
		= { 150, 150, 250 };

	// プレイヤー引き寄せ攻撃で当たった敵１体ごとに増える振動強度の値
	const int VIBRATION_POWER_PLAYER_ATTRACT_ATTACK_COLL_PER_ONE = 250;
	// プレイヤー引き寄せ攻撃での振動強度の最大
	const int VIBRATION_POWER_MAX_PLAYER_ATTRACT_ATTACK = 800;
	// プレイヤー引き寄せ攻撃での振動時間
	const int VIBRATION_TIME_PLAYER_ATTRACT_ATTACK = 230;

	// プレイヤー被ダメージ時の振動強度
	const int VIBRATION_POWER_PLAYER_DAMAGE = 500;
	// プレイヤー被ダメージ時の振動時間
	const int VIBRATION_TIME_PLAYER_DAMAGE = 300;
}