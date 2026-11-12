#include "SwordBase.h"
#include "SwordValue.h"

SwordBase::SwordBase()
{
	parent = nullptr;
}

SwordBase::~SwordBase()
{
}

void SwordBase::Update()
{
	DynamicObjBase::Update();
	transform.position += velocity * Time::GameDeltaTime();
}

void SwordBase::Draw()
{
	DynamicObjBase::Draw();
}
