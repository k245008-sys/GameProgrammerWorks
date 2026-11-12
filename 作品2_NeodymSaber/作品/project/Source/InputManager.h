#pragma once
#include "../Library/myDxLib.h"
#include "KeyInput.h"
#include "ButtonInput.h"
#include "StickInput.h"
#include "TriggerInput.h"

/*
	“ü—Íî•ñ‚ğ‚Á‚½‘S‚Ä‚ÌƒNƒ‰ƒX‚ğŠÇ—‚·‚éƒNƒ‰ƒX
	ˆ»•”
*/

class InputManager : public GameObject
{
public:
	InputManager(SceneBase* _scene);
	void Update()override;

	bool IsPadPush(const std::string& _name);
	bool IsPadPushDown(const std::string& _name);
	bool CheckPadPushAllDown();

	bool IsKeyPush(const std::string& _name);
	bool IsKeyPushDown(const std::string& _name);
	bool CheckKeyPushAllDown();
	bool IsKeyPushDir(const bool& _rSide);

	// ŒX‚¯‚Ä‚¢‚é‚©
	bool IsStickTilt(const std::string& _name) { return stick.IsTilt(_name); }
	// ŒX‚¯‚½uŠÔ‚©
	bool IsStickTiltDown(const std::string& _name) { return stick.IsTiltDown(_name); }
	// ŒX‚¯‚½‚Æ‚«‚Ì“ü—ÍˆÊ’u
	VECTOR2I GetStickPos(const std::string& _name) { return stick.GetPos(_name); }
	// ŒX‚¯‚½•ûŒü‚ÌŠp“x
	float GetStickAngle(const std::string& _name) { return stick.GetAngle(_name); }
	// ’[‚Ü‚Å‚Ç‚ê‚­‚ç‚¢ŒX‚¯‚½‚©‚ÌŠ„‡
	float GetStickTiltRate(const std::string& _name) { return stick.GetTiltRate(_name); }
	float GetStickOrKeyDirAngle(const bool& _rSide);

	bool GetEnableVib() { return enableVib; }

	bool IsTriggerPush(const std::string& _name) { return trigger.IsPush(_name); }
	bool IsTriggerPushDown(const std::string& _name) { return trigger.IsPushDown(_name); }
	// ‰Ÿ‚µ‚½[‚³‚Ì’l
	unsigned char GetTriggerPushAmount(const std::string& _name) { return trigger.GetPushAmount(_name); }

	bool IsStickTiltOrKeyPushDir(const bool& _rSide);
	VECTOR2I GetStickOrKeyPos(const bool& _rSide);

private:
	KeyInput key;
	ButtonInput pad;
	StickInput stick;
	TriggerInput trigger;

	bool enableVib;
};