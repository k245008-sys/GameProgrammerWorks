#include "RoundShadowManager.h"
#include "RoundShadow.h"
#include <algorithm>

RoundShadowManager::RoundShadowManager()
{
	shadows.clear();
}

RoundShadowManager::~RoundShadowManager()
{
	shadows.clear();
}

void RoundShadowManager::Draw()
{
	for (auto& s : shadows)
		s->Draw();
}

void RoundShadowManager::Add(RoundShadow* _shadow)
{
	shadows.emplace_back(_shadow);
}
