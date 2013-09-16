#include "InventoryObject.h"


InventoryObject::InventoryObject(void)
{
	toolType = Default;
	toolLevel = 1;
}


InventoryObject::~InventoryObject(void)
{
}

void InventoryObject::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
}
