#include "Actionbar.h"
#include <typeinfo>
#include "main.h"
#include "SDL_TTF.h"


Actionbar::Actionbar(void)
{
	barObjects = NULL;

	objectsStartOffsetX = 120;
	objectsStartOffsetY = 100;
	
	objectSize = 64;

	actionbarSize = 8;

	SCREEN_HEIGHT_old = 0;
	SCREEN_WIDTH_old = 0;

	setScreenSize();
}


Actionbar::~Actionbar(void)
{
}

void Actionbar::setScreenSize()
{

	if (SCREEN_WIDTH_old != SCREEN_WIDTH || SCREEN_WIDTH_old != SCREEN_WIDTH)
	{
		SCREEN_WIDTH_old = SCREEN_WIDTH;
		SCREEN_WIDTH_old = SCREEN_WIDTH;

		actionbarX = SCREEN_WIDTH/2-372;
		actionbarY = SCREEN_HEIGHT-160;
	
		delete[] barObjects;

		barObjects = new InventoryObject*[actionbarSize];
		for (int32_t i = 0; i<actionbarSize; i++)
		{
			barObjects[i] = NULL;
		}
	}
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
	setScreenSize();

	SDL_Surface* inventoryToolbar = NULL;
	inventoryToolbar = load_image("GUI/InventoryToolbar.png");
	apply_surface(actionbarX, actionbarY, inventoryToolbar, screen);
	for (int32_t i = 0; i<actionbarSize; i++)
	{
		if (barObjects[i] != NULL)
		{
			barObjects[i]->draw(actionbarX+objectsStartOffsetX+i*objectSize, actionbarY+objectsStartOffsetY);
		}
	}

	apply_surface(actionbarX+objectsStartOffsetX+world.player.activeAction*objectSize, actionbarY+objectsStartOffsetY, load_image("GUI/inventoryActive.png"), screen);
}


void Actionbar::onMouseDown()
{
	int xRelativeToItems = mouseX - actionbarX - objectsStartOffsetX;
	int yRelativeToItems = mouseY - actionbarY - objectsStartOffsetY;

	if (xRelativeToItems < 0 || xRelativeToItems > actionbarSize*objectSize
		|| yRelativeToItems<0 || yRelativeToItems > objectSize )
	{
		return;
	}

	int droppedIndex = xRelativeToItems/objectSize;

	world.player.activeAction = droppedIndex;
}

void Actionbar::onMouseUp()
{
	int xRelativeToItems = mouseX - actionbarX - objectsStartOffsetX;
	int yRelativeToItems = mouseY - actionbarY - objectsStartOffsetY;

	if (xRelativeToItems < 0 || xRelativeToItems > actionbarSize*objectSize
		|| yRelativeToItems<0 || yRelativeToItems > objectSize )
	{
		return;
	}

	int droppedIndex = xRelativeToItems/objectSize;

	if (world.player.inventory.draggingIndex != -1)
	{
		barObjects[droppedIndex] = world.player.inventory.objects[world.player.inventory.draggingIndex];
	}
}
	
