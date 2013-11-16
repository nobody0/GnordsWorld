#include "Actionbar.h"
#include <typeinfo>
#include "main.h"
#include "SDL_TTF.h"


Actionbar::Actionbar(void)
{
	actionbarX = SCREEN_WIDTH/2-372;
	actionbarY = SCREEN_HEIGHT-160;

	objectsStartOffsetX = 120;
	objectsStartOffsetY = 100;

	objectSize = 64;

	actionbarSize = 8;
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
	
