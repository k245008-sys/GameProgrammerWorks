#include "ButtonInput.h"

ButtonInput::ButtonInput()
{
	controller = 0;

	AddInfo("1", PAD_INPUT_1);	// Xbox:A
	AddInfo("2", PAD_INPUT_2);	// Xbox:B
	AddInfo("3", PAD_INPUT_3);	// Xbox:X
	AddInfo("4", PAD_INPUT_4);	// Xbox:Y
	AddInfo("5", PAD_INPUT_5);	// Xbox:L
	AddInfo("6", PAD_INPUT_6);	// Xbox:R
	AddInfo("Left", PAD_INPUT_LEFT);
	AddInfo("Right", PAD_INPUT_RIGHT);
	AddInfo("Up", PAD_INPUT_UP);
	AddInfo("Down", PAD_INPUT_DOWN);
	AddInfo("All", DX_CHECKINPUT_PAD);
}

ButtonInput::~ButtonInput()
{
	infos.clear();
}

void ButtonInput::Update()
{
	controller = GetJoypadInputState(ctrlNo);

	for (auto& info : infos)
	{
		PushInputInfo& bInfo = info.second;
		bInfo.isInput.last = bInfo.isInput.current;
		if (info.first == "All")
		{
			bInfo.isInput.current = CheckHitKeyAll(bInfo.type);
			continue;
		}
		bInfo.isInput.current = ((controller & bInfo.type) != 0);
	}
}
