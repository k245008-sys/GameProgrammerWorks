#include "InputManager.h"

InputManager::InputManager(SceneBase* _scene) : GameObject(_scene)
{
	pad.SetControllerNo(DX_INPUT_PAD1);
	stick.SetControllerNo(DX_INPUT_PAD1);
	trigger.SetControllerNo(DX_INPUT_PAD1);

	enableVib = true;
}

void InputManager::Update()
{
	key.Update();
	pad.Update();
	stick.Update();
	trigger.Update();

#ifdef _DEBUG
	if (IsKeyPushDown("V"))
		enableVib = enableVib ? false : true;
#endif
}

bool InputManager::IsPadPush(const std::string& _name)
{
	return pad.GetInfo(_name).isInput.current;
}

bool InputManager::IsPadPushDown(const std::string& _name)
{
	bool last = pad.GetInfo(_name).isInput.last;
	bool current = pad.GetInfo(_name).isInput.current;
	return (!last && current);
}

bool InputManager::CheckPadPushAllDown()
{
	bool last = pad.GetInfo("All").isInput.last;
	bool current = pad.GetInfo("All").isInput.current;
	return (!last && current);
}

bool InputManager::IsKeyPush(const std::string& _name)
{
	return key.GetInfo(_name).isInput.current;
}

bool InputManager::IsKeyPushDown(const std::string& _name)
{
	bool last = key.GetInfo(_name).isInput.last;
	bool current = key.GetInfo(_name).isInput.current;
	return (!last && current);
}

bool InputManager::CheckKeyPushAllDown()
{
	bool last = key.GetInfo("All").isInput.last;
	bool current = key.GetInfo("All").isInput.current;
	return (!last && current);
}

bool InputManager::IsKeyPushDir(const bool& _rSide)
{
	if (_rSide)
	{
		if (IsKeyPush("Up"))
			return true;
		else if (IsKeyPush("Down"))
			return true;
		if (IsKeyPush("Right"))
			return true;
		else if (IsKeyPush("Left"))
			return true;
	}
	else
	{
		if (IsKeyPush("W"))
			return true;
		else if (IsKeyPush("S"))
			return true;
		if (IsKeyPush("D"))
			return true;
		else if (IsKeyPush("A"))
			return true;
	}
	return false;
}

float InputManager::GetStickOrKeyDirAngle(const bool& _rSide)
{
	bool up = IsKeyPush("W");
	bool down = IsKeyPush("S");
	bool right = IsKeyPush("D");
	bool left = IsKeyPush("A");
	if (_rSide)
	{
		up = IsKeyPush("Up");
		down = IsKeyPush("Down");
		right = IsKeyPush("Right");
		left = IsKeyPush("Left");
	}
	float rot = 0;
	if (up)
		rot = 0;
	else if (down)
		rot = DEGREE * 180;
	if (right)
		rot = DEGREE * 90;
	else if (left)
		rot = DEGREE * -90;
	if (up && right)
		rot = DEGREE * 45;
	else if (up && left)
		rot = DEGREE * -45;
	if (down && right)
		rot = DEGREE * 135;
	else if (down && left)
		rot = DEGREE * -135;

#ifndef _DEBUG
	rot = 0;
	up = false;
#endif
	if (rot == 0 && !up)
	{
		if (_rSide)
			rot = GetStickAngle("R");
		else
			rot = GetStickAngle("L");
	}
	return rot;
}

bool InputManager::IsStickTiltOrKeyPushDir(const bool& _rSide)
{
	if (_rSide)
	{
		if (IsStickTilt("R"))
			return true;
	}
	else
	{
		if (IsStickTilt("L"))
			return true;
	}
#ifdef _DEBUG
	return IsKeyPushDir(_rSide);
#endif
	return false;
}

VECTOR2I InputManager::GetStickOrKeyPos(const bool& _rSide)
{
	bool up = IsKeyPush("W");
	bool down = IsKeyPush("S");
	bool right = IsKeyPush("D");
	bool left = IsKeyPush("A");
	std::string side = "L";
	if (_rSide)
	{
		up = IsKeyPush("Up");
		down = IsKeyPush("Down");
		right = IsKeyPush("Right");
		left = IsKeyPush("Left");
		side = "R";
	}

	if (IsStickTilt(side))
	{
		return GetStickPos(side);
	}
	else
	{
		if (up)
			return VECTOR2I(0, STICK_INPUT_MAX);
		if (down)
			return VECTOR2I(0, -STICK_INPUT_MAX);
		if (right)
			return VECTOR2I(STICK_INPUT_MAX, 0);
		if (left)
			return VECTOR2I(-STICK_INPUT_MAX, 0);
	}
	return VECTOR2I();
}
