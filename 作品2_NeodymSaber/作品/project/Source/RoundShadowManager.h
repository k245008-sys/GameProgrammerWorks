#pragma once
#include "../Library/gameObject.h"
#include <list>

class RoundShadow;

class RoundShadowManager : public GameObject
{
public:
	RoundShadowManager();
	~RoundShadowManager();
	void Draw()override;

	void Add(RoundShadow* _shadow);

private:
	std::list<RoundShadow*> shadows;
};