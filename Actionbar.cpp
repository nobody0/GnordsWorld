#include "Actionbar.h"
#include <typeinfo>
#include "main.h"
#include "SDL_TTF.h"


Actionbar::Actionbar(void)
{
	actionbarSize = 9;
	barObjects = new InventoryObject*[actionbarSize];
	for (int32_t i = 0; i<actionbarSize; i++)
	{
		barObjects[i] = NULL;
	}
}


Actionbar::~Actionbar(void)
{
}


void Actionbar::add(InventoryObject* inventoryObject, int index)
{
	barObjects[index] = inventoryObject;
}

void Actionbar::remove(int index)
{
	barObjects[index] = NULL;
}

void Actionbar::draw()
{
	int actionbarX = SCREEN_WIDTH/2-372;
	int actionbarY = SCREEN_HEIGHT-160;

	SDL_Surface* inventoryToolbar = NULL;
	inventoryToolbar = load_image("GUI/InventoryToolbar.png");
	apply_surface(actionbarX, actionbarY, inventoryToolbar, screen);
	for (int32_t i = 0; i<actionbarSize; i++)
	{
		if (barObjects[i] != NULL)
		{
			barObjects[i]->actionbarDraw(actionbarX+120+(i*64), actionbarY+100, i);
		}
	}
}



	
