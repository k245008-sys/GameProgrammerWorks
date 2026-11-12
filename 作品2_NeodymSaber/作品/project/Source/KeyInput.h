#pragma once
#pragma once
#include "InputBase.h"

/*
	PCのキー入力取得クラス
	綾部
*/

class KeyInput : public InputBase<PushInputInfo>
{
public:
	KeyInput();
	~KeyInput();
	void Update()override;
};