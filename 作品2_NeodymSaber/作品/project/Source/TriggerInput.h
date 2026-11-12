#pragma once
#include "InputBase.h"
#include "../Library/myDxLib.h"

/*
	パッドのトリガー入力取得クラス
	綾部
*/

namespace
{
	// 最大押下とする判定基準の深さ
	const int TRIGGER_INPUT_MAX = 255;
}

class TriggerInput : public InputBase<TriggerInputInfo>
{
public:
	TriggerInput();
	~TriggerInput();
	void Update()override;

	unsigned char GetPushAmount(const std::string& _name);
	bool IsPush(const std::string& _name);
	bool IsPushDown(const std::string& _name);
};