#pragma once
#include "InputBase.h"

/*
	パッドのボタン入力取得クラス
	綾部
*/

class ButtonInput : public InputBase<PushInputInfo>
{
public:
	ButtonInput();
	~ButtonInput();
	void Update()override;

private:
	int controller;
};