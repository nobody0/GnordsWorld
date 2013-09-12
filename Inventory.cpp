#include "Inventory.h"
#include <typeinfo>
#include "main.h"

Inventory::Inventory(void)
{
	inventorySize = 10;
	objects = new InventoryObject*[inventorySize];
	for (int32_t i = 0; i<inventorySize; i++)
	{
		objects[i] = NULL;
	}
}


Inventory::~Inventory(void)
{
}


bool Inventory::add(InventoryObject* inventoryObject)
{
	const type_info &newType = typeid(*inventoryObject);
	int32_t firstEmptySlot = -1;

	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] == NULL)
		{
			if (firstEmptySlot == -1)
			{
				firstEmptySlot = i;
			}
		}
		else if (newType == typeid(*objects[i]))
		{
			objects[i]->amount += inventoryObject->amount;
			delete inventoryObject;
			return true;
		}
	}

	if (firstEmptySlot != -1)
	{
		world.player.activeTool = inventoryObject;
		objects[firstEmptySlot] = inventoryObject;
		return true;
	}

	delete inventoryObject;
	return false;
}