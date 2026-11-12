#include "EnemyStateBase.h"
#include "EnemyBase.h"

void EnemyStateBase::SetParent(DynamicObjBase* _parent)
{
	parent = dynamic_cast<EnemyBase*>(_parent);
}