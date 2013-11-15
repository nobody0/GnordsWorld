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
	//Hier kommt Die Draw aller Objekte und danach die Draw Active hin.
	
	SDL_Surface* border = NULL;
	border = load_image("GUI/InventoryBackgroundRamen.png");
	apply_surface(SCREEN_WIDTH/2-282, SCREEN_HEIGHT/2-130, border, screen);
}

void Inventory::drawToolbar()
{
	SDL_Surface* inventoryToolbar = NULL;
	inventoryToolbar = load_image("GUI/InventoryToolbar.png");
	apply_surface(SCREEN_WIDTH/2-372, SCREEN_HEIGHT-160, inventoryToolbar, screen);
}
	//TODO Über alle Objekte iterieren und von jedem die Draw aufrufen. Jedem in ScreenKoordinaten sagen wo es sich zeichnen soll
	//TODO Draw Active (Fehlt logic)
	
