#pragma once
#include <unordered_map>
#include <string>

/*
	モデルごとにモーション(アニメーション)の
	管理をするためのクラス
	綾部
*/

// まとめて値を設定する用
struct AnimSetting
{
	bool isLoop;
	float startFrame;
	float frameSpeed;
	float blendFrame;
};

namespace
{
	const AnimSetting DEFAULT_ANIM_SETTING = { false, 0, 1.0f, 10 };

	AnimSetting AGet(const bool& _isLoop = DEFAULT_ANIM_SETTING.isLoop,
		const float& _startFrame = DEFAULT_ANIM_SETTING.startFrame,
		const float& _frameSpeed = DEFAULT_ANIM_SETTING.frameSpeed,
		const float& _blendFrame = DEFAULT_ANIM_SETTING.blendFrame)
	{
		AnimSetting set = AnimSetting();
		set.isLoop = _isLoop;
		set.startFrame = _startFrame;
		set.frameSpeed = _frameSpeed;
		float blendFrame = _blendFrame;
		if (_blendFrame <= 0)
			blendFrame = 1.0f;
		set.blendFrame = blendFrame;

		return set;
	}
}

class Animator
{
public:
	Animator();
	~Animator();
	void Update();

	Animator* Clone() const
	{
		Animator* a = new Animator();
		a->infos = this->infos;
		a->hModel = -1;
		a->blendRate = 1.0f;
		a->currentAnimName = "None";
		a->beforeAnimName = "None";
		return a;
	}

	float GetBlendFrame(const std::string& _name) { return infos[_name].blendFrame; }
	float GetDefBlendFrame(const std::string& _name) { return infos[_name].defBlendFrame; }

	void SetModel(const int& _hModel) { hModel = _hModel; }
	void SetBlendFrame(const std::string& _name, const float& _blendFrame) { infos[_name].blendFrame = _blendFrame; }
	/// <summary>
	/// アニメーションを読み込んで登録する
	/// </summary>
	/// <param name="_name">管理用番号</param>
	/// <param name="_filename">アニメーション素材のパス</param>
	/// <param name="_animSetting">設定する値</param>
	void LoadFile(const std::string& _name, const std::string& _filename, const AnimSetting& _animSetting = DEFAULT_ANIM_SETTING);
	// 再生(既に再生中ならreturn)
	void Play(const std::string& _name);
	// 現在再生中のアニメーションが終了したらtrue
	bool IsFinish();

	std::string GetPlay() { return currentAnimName; }

	void ResetCurrentFrame() { infos[currentAnimName].currentFrame = 0; }
	void ResetBlendFrame(const std::string& _name) { infos[_name].blendFrame = infos[_name].defBlendFrame; }

private:
	// 再生フレームを進める
	void PlayingFrame(const std::string& _name);

	// アニメーションが持つ情報
	struct AnimInfo
	{
		int handle;
		int attachID;
		float startFrame;
		float currentFrame;
		float frameSpeed;
		float frameMax;
		float defBlendFrame;
		float blendFrame;
		bool isLoop;
		bool isFirstLoop;
		AnimInfo() : handle(-1), attachID(-1), startFrame(0), currentFrame(0), frameSpeed(0), frameMax(0),
			defBlendFrame(0), blendFrame(0), isLoop(false), isFirstLoop(false) {
		}
	};
	std::unordered_map<std::string, AnimInfo>infos;

	int hModel;
	std::string currentAnimName;
	std::string beforeAnimName;
	float blendRate;
};