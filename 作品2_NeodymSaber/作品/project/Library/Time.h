#pragma once
/*
	現実で1フレームごとに経過した時間と
	ゲーム内でスローにしたりする用の時間
	を持つ
	綾部
*/

namespace Time {
	void Init();
	void RefreshRealDeltaTime();
	float RealDeltaTime();
	void SetGameDeltaTime(const float& _gameDeltaTime);
	float GameDeltaTime();
};
