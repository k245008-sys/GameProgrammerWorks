#include "Animator.h"
#include "../Library/myDxLib.h"
#include <assert.h>


Animator::Animator()
{
	infos.clear();
	hModel = -1;
	blendRate = 1.0f;
	currentAnimName = "None";
	beforeAnimName = "None";
}

Animator::~Animator()
{
	for (auto& info : infos)
	{
		if(info.second.handle > 0)
		MV1DeleteModel(info.second.handle);
	}
}

void Animator::Update()
{
	if (currentAnimName == "None")
		return;

	if (blendRate >= 1.0f)
	{
		// 再生フレームを進める
		PlayingFrame(currentAnimName);
		AnimInfo ai = infos[currentAnimName];
		MV1SetAttachAnimTime(hModel, ai.attachID, ai.currentFrame);
		return;
	}

	// 直前アニメ―ションと現在アニメ―ションの補間
	blendRate += 1.0f / infos[currentAnimName].blendFrame;
	if (blendRate > 1.0f)
		blendRate = 1.0f;

	MV1SetAttachAnimBlendRate(hModel, infos[currentAnimName].attachID, blendRate);
	MV1SetAttachAnimBlendRate(hModel, infos[beforeAnimName].attachID, 1.0f - blendRate);

	// 補間が終わったら直前アニメ―ションを無効にする
	if (blendRate >= 1.0f)
	{
		MV1DetachAnim(hModel, infos[beforeAnimName].attachID);
		beforeAnimName = "None";
	}
}

void Animator::LoadFile(const std::string& _name, const std::string& _filename, const AnimSetting& _animSetting)
{
	AnimInfo ai;
	ai.handle = MV1LoadModel(_filename.c_str());
	assert(ai.handle > 0);
	ai.isLoop = _animSetting.isLoop;
	ai.startFrame = _animSetting.startFrame;
	ai.frameSpeed = _animSetting.frameSpeed;
	ai.defBlendFrame = _animSetting.blendFrame;
	ai.blendFrame = _animSetting.blendFrame;
	infos.insert({_name, ai});
}

void Animator::Play(const std::string& _name)
{
	if ((int)infos.count(_name) == FALSE)
		return;

	if (currentAnimName == _name)
	{
		infos[currentAnimName].currentFrame = infos[currentAnimName].startFrame;
		return;
	}

	if (beforeAnimName != "None")
	{
		MV1DetachAnim(hModel, infos[beforeAnimName].attachID);
		infos[beforeAnimName].attachID = -1;
		beforeAnimName = "None";
	}
	if (currentAnimName != "None")
	{
		beforeAnimName = currentAnimName;
		blendRate = 0.0f;
	}

	infos[_name].attachID = MV1AttachAnim(hModel, 0, infos[_name].handle);
	infos[_name].frameMax = MV1GetAttachAnimTotalTime(hModel, infos[_name].attachID);
	infos[_name].currentFrame = infos[_name].startFrame;
	currentAnimName = _name;
}

bool Animator::IsFinish()
{
	if (infos[currentAnimName].currentFrame >= infos[currentAnimName].frameMax ||
		infos[currentAnimName].isFirstLoop)
		return true;
	return false;
}

void Animator::PlayingFrame(const std::string& _name)
{
	if (_name == "None")
		return;

	AnimInfo& ai = infos[_name];
	ai.isFirstLoop = false;

	ai.currentFrame += ai.frameSpeed;
	// ループ処理
	if (ai.currentFrame >= ai.frameMax)
	{
		if (ai.isLoop)
		{
			ai.currentFrame -= ai.frameMax;
			ai.isFirstLoop = true;
		}
		else
		{
			ai.currentFrame = ai.frameMax;
		}
	}
}
