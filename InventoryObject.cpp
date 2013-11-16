#include "InventoryObject.h"
#include "main.h"


InventoryObject::InventoryObject(void)
{
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

void InventoryObject::drawActive(int x, int y)
{
	apply_surface(x-imageActive->w/2, y-imageActive->h/2, imageActive, screen);
}


void InventoryObject::draw(int x, int y)
{
	apply_surface(x, y, image, screen);
}