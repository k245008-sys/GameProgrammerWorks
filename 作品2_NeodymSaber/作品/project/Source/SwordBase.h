#pragma once
#include "DynamicObjBase.h"

/*
	Œ•‚ÌŠî’êƒNƒ‰ƒX
	ˆ»•”
*/

class Player;

class SwordBase : public DynamicObjBase
{
public:
	SwordBase();
	virtual ~SwordBase();
	virtual void Update()override;
	virtual void Draw()override;

	Player* GetParent() { return parent; }

	void SetParent(Player* _parent) { parent = _parent; }

protected:
	Player* parent;
};