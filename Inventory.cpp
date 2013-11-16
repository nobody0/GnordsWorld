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
		else if (objects[i]->name == inventoryObject->name && objects[i]->amount + inventoryObject->amount <= objects[i]->maxAmount) 
		{
			objects[i]->amount += inventoryObject->amount;
			delete inventoryObject;
			return true;
		}
	}

	if (firstEmptySlot != -1)
	{
		actionbar.barObjects[0] = inventoryObject;
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
					for (int32_t ii = 0; ii<actionbar.actionbarSize; ii++)
					{
						if (objects[ii] == objects[i])
						{
							actionbar.remove(ii);
						}
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

void Inventory::draw()
{
	int backgroundX = SCREEN_WIDTH/2-282;
	int backgroundY = SCREEN_HEIGHT/2-130;
	int columnCount = 8;

	SDL_Surface* background = NULL;
	background = load_image("GUI/InventoryBackground.png");
	apply_surface(backgroundX, backgroundY, background, screen);
	
	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] != NULL)
		{
			int itemX = i%columnCount;
			int itemY = i/columnCount;
			objects[i]->draw(backgroundX + itemX*64+28, backgroundY + itemY*64+28);
		}
	}	
	SDL_Surface* border = NULL;
	border = load_image("GUI/InventoryBackgroundRamen.png");
	apply_surface(SCREEN_WIDTH/2-282, SCREEN_HEIGHT/2-130, border, screen);
}

void Inventory::drawToolbar()
{
	actionbar.draw();
}
	
	//TODO Draw Active (Fehlt logic)
	
