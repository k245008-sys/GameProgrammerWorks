#include "KeyInput.h"
#include <assert.h>

KeyInput::KeyInput()
{
	AddInfo("1", KEY_INPUT_1);
	AddInfo("2", KEY_INPUT_2);
	AddInfo("3", KEY_INPUT_3);
	AddInfo("4", KEY_INPUT_4);
	AddInfo("5", KEY_INPUT_5);
	AddInfo("6", KEY_INPUT_6);
	AddInfo("7", KEY_INPUT_7);
	AddInfo("8", KEY_INPUT_8);
	AddInfo("9", KEY_INPUT_9);
	AddInfo("0", KEY_INPUT_0);
	AddInfo("Q", KEY_INPUT_Q);
	AddInfo("W", KEY_INPUT_W);
	AddInfo("E", KEY_INPUT_E);
	AddInfo("R", KEY_INPUT_R);
	AddInfo("T", KEY_INPUT_T);
	AddInfo("Y", KEY_INPUT_Y);
	AddInfo("U", KEY_INPUT_U);
	AddInfo("I", KEY_INPUT_I);
	AddInfo("O", KEY_INPUT_O);
	AddInfo("P", KEY_INPUT_P);
	AddInfo("A", KEY_INPUT_A);
	AddInfo("S", KEY_INPUT_S);
	AddInfo("D", KEY_INPUT_D);
	AddInfo("F", KEY_INPUT_F);
	AddInfo("G", KEY_INPUT_G);
	AddInfo("H", KEY_INPUT_H);
	AddInfo("J", KEY_INPUT_J);
	AddInfo("K", KEY_INPUT_K);
	AddInfo("L", KEY_INPUT_L);
	AddInfo("Z", KEY_INPUT_Z);
	AddInfo("X", KEY_INPUT_X);
	AddInfo("C", KEY_INPUT_C);
	AddInfo("V", KEY_INPUT_V);
	AddInfo("B", KEY_INPUT_B);
	AddInfo("N", KEY_INPUT_N);
	AddInfo("M", KEY_INPUT_M);

	AddInfo("Semicolon", KEY_INPUT_SEMICOLON);

	AddInfo("Left", KEY_INPUT_LEFT);
	AddInfo("Right", KEY_INPUT_RIGHT);
	AddInfo("Up", KEY_INPUT_UP);
	AddInfo("Down", KEY_INPUT_DOWN);

	AddInfo("Space", KEY_INPUT_SPACE);
	AddInfo("All", DX_CHECKINPUT_ALL);
}

KeyInput::~KeyInput()
{
	infos.clear();
}

void KeyInput::Update()
{
	for (auto& info : infos)
	{
		PushInputInfo& kInfo = info.second;
		kInfo.isInput.last = kInfo.isInput.current;
		if (info.first == "All")
		{
			kInfo.isInput.current = CheckHitKeyAll(kInfo.type);
			continue;
		}
		kInfo.isInput.current = CheckHitKey(kInfo.type);
	}
}
