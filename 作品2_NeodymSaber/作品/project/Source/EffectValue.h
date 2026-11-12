#pragma once

inline namespace Effect
{
	struct EffectSetting
	{
		float playSpeed;
		bool isLoop;
		VECTOR scale;
		EffectSetting() : playSpeed(1.0f), isLoop(false), scale(VGet(1, 1, 1)) {}
	};
}

namespace
{
	inline EffectSetting EGet(const float& _playSpeed = 1.0f,
		const bool& _isLoop = false, const VECTOR& _scale = VGet(1, 1, 1))
	{
		EffectSetting info;
		info.playSpeed = _playSpeed;
		info.isLoop = _isLoop;
		info.scale = _scale;
		return info;
	}

	const EffectSetting EFFECT_HIT_SETTING = EGet(5.0f, false, VGet(10, 10, 10));
	const EffectSetting EFFECT_ATTRACT_RANGE_RED_SETTING = EGet(2.0f, true, VGet(0.1f, 0.1f, 0.1f));
	const EffectSetting EFFECT_SNAP_UNION_SETTING = EGet(4.4f, false, VGet(50, 50, 50));
	const EffectSetting EFFECT_SHOT_SETTING = EGet(2.0f, true, VGet(14, 14, 14));

	const VECTOR EFFECT_HIT_ADJUST_POS = VGet(0, 120.0f, 0.0f);
	const VECTOR EFFECT_ADJUST_SNAP_UNION_POS = VGet(0, 120.0f, -150.0f);
	
	const float EFFECT_HIT_DEAD_SCALE = 10.0f;
	const float EFFECT_HIT_EXPLOSION_MYSELF_SCALE = 15.0f;
	const float EFFECT_HIT_EXPLOSION_AROUND_SCALE = 1.0f;
	const float EFFECT_PLAYER_ATTRACT_ATTACK_HIT_SCALE = 5.0f;
}