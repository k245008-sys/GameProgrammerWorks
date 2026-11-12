#include "TriggerInput.h"

TriggerInput::TriggerInput()
{
	AddInfo("L");
	AddInfo("R");
}

TriggerInput::~TriggerInput()
{
	infos.clear();
}

void TriggerInput::Update()
{
	for (auto &info : infos)
	{
		TriggerInputInfo& tInfo = info.second;
		tInfo.isInput.last = tInfo.isInput.current;
	}
	// ‰Ÿ‚µ‚½[‚³‚ðŽæ“¾
	XINPUT_STATE xInput;
	GetJoypadXInputState(ctrlNo, &xInput);
	infos["L"].pushAmount = xInput.LeftTrigger;
	infos["R"].pushAmount = xInput.RightTrigger;
	for (auto& info : infos)
	{
		TriggerInputInfo& tInfo = info.second;
		tInfo.isInput.current = (tInfo.pushAmount >= TRIGGER_INPUT_MAX);
	}
}

unsigned char TriggerInput::GetPushAmount(const std::string& _name)
{
	return infos[_name].pushAmount;
}

bool TriggerInput::IsPush(const std::string& _name)
{
	return infos[_name].isInput.current;
}

bool TriggerInput::IsPushDown(const std::string& _name)
{
	return (!infos[_name].isInput.last &&
		infos[_name].isInput.current);
}
