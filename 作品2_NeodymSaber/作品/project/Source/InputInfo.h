#pragma once
#include "../Library/gameObject.h"
#include "DataOfChange.h"

#include <string>

/*
	入力データの保存に必要な情報を持つ各クラス
	綾部
*/

class InputInfoBase
{
public:
	InputInfoBase() {}
	DataOfChange<bool> isInput; // 現在と直前の入力有無
};

// パッドとキー
class PushInputInfo : public InputInfoBase
{
public:
	PushInputInfo() : type(0) {}
	int type;
};

// パッドスティック
class StickInputInfo : public InputInfoBase
{
public:
	StickInputInfo() : angle(0), tiltRate(0) {}
	VECTOR2I pos;
	float angle; // スティックを傾けた方向の角度
	float tiltRate; // スティックを傾けている角度
};

// パッドトリガー
class TriggerInputInfo : public InputInfoBase
{
public:
	TriggerInputInfo() : pushAmount(0) {}
	unsigned char pushAmount; // 押された深さ
};