#include "SwordStateBase.h"
#include "SwordBase.h"

void SwordStateBase::SetParent(DynamicObjBase* _parent)
{
	parent = dynamic_cast<SwordBase*>(_parent);
}
