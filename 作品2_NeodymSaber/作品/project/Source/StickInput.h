#pragma once
#include "InputBase.h"
#include "../Library/myDxLib.h"

/*
	パッドのスティック入力取得クラス
	綾部
*/

namespace
{
	// スティック移動値の最大
	const int STICK_INPUT_MAX = 1000;
}

class StickInput : public InputBase<StickInputInfo>
{
public:
	StickInput();
	~StickInput();
	void Update()override;

	// 傾けているか
	bool IsTilt(const std::string& _name) { return infos[_name].isInput.current; }
	// 傾けた瞬間か
	bool IsTiltDown(const std::string& _name) { return (!infos[_name].isInput.last && infos[_name].isInput.current); }
	// 傾けた位置
	VECTOR2I GetPos(const std::string& _name) { return infos[_name].pos; }
	/* 
	   傾けた方向の角度(管理しやすいよう上方向を０度の基準に
	   右半分１８０度、左半分－１８０度にしている)
	*/
	float GetAngle(const std::string& _name) { return infos[_name].angle; }
	// 端までどれくらい傾けたかの割合
	float GetTiltRate(const std::string& _name) { return infos[_name].tiltRate; }
};