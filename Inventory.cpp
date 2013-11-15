#include "Inventory.h"
#include <typeinfo>
#include "main.h"


Inventory::Inventory(void)
{
	inventorySize = 48;
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
			//TODO Maximalgröße der stacks.
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

bool Inventory::remove(std::string name, int deltaAmount)
{
	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] != NULL && objects[i]->name == name) 
		{
			if (objects[i]->amount >= deltaAmount)
			{
				objects[i]->amount -= deltaAmount;
				if (objects[i]->amount == 0)
				{	
					//TODO Überprüfen ob in der Toolbar wenn ja auch dort entfernen
					if (objects[i] == world.player.activeTool)
					{
						world.player.activeTool = NULL;
					}
					delete objects[i];
					objects[i] = NULL;
				}
				return true;
			}
		}
	}
	return false;
}


bool Inventory::hasObject(std::string name, int amount)
{
	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] != NULL && objects[i]->name == name) 
		{
			if (objects[i]->amount >= amount)
			{
				return true;
			}
		}
	}
	return false;
}



//Ich benutze ein Erde. 
//Stacksize im Inventar soll sich um deltaAmount reduzieren
//Wenn Stack dadurch auf null reduziert wird soll das Objekt aus dem Inventar, aus der toolbar und als Active tool entfernt werden.
