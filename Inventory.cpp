#include "Inventory.h"
#include <typeinfo>
#include "main.h"


Inventory::Inventory(void)
{
	backgroundX = SCREEN_WIDTH/2-282;
	backgroundY = SCREEN_HEIGHT/2-130;
	columnCount = 8;
	rowCount = 6;

	objectsStartOffsetX = 28;
	objectsStartOffsetY = 28;

	objectSize = 64;

	inventorySize = columnCount * rowCount;
	objects = new InventoryObject*[inventorySize];
	for (int32_t i = 0; i<inventorySize; i++)
	{
		objects[i] = NULL;
	}

	draggingIndex = -1;
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
			if (remove(i, deltaAmount))
			{
				return true;
			}
		}
	}
	return false;
}

bool Inventory::remove(InventoryObject* object, int deltaAmount)
{
	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] == object) 
		{
			if (remove(i, deltaAmount))
			{
				return true;
			}
		}
	}
	return false;
}

bool Inventory::remove(int i, int deltaAmount)
{
	if (objects[i]->amount >= deltaAmount)
	{
		objects[i]->amount -= deltaAmount;
		if (objects[i]->amount == 0)
		{	
			for (int32_t ii = 0; ii<actionbar.actionbarSize; ii++)
			{
				if (actionbar.barObjects[ii] == objects[i])
				{
					actionbar.remove(ii);
				}
			}
			delete objects[i];
			objects[i] = NULL;
		}
		return true;
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

void Inventory::swap(int index1, int index2)
{
	if (objects[index1] != NULL && objects[index2] != NULL && objects[index1]->name == objects[index2]->name)
	{
		objects[index2]->amount += objects[index1]->amount;

		if (objects[index2]->amount > objects[index2]->maxAmount)
		{
			objects[index1]->amount = objects[index2]->amount-objects[index2]->maxAmount;
			objects[index2]->amount = objects[index2]->maxAmount;
		}
		else
		{
			remove(index1, objects[index1]->amount);
		}
	}
	else
	{
		InventoryObject* temp = objects[index1];
		objects[index1] = objects[index2];
		objects[index2] = temp;
	}
}

void Inventory::draw()
{
	SDL_Surface* background = NULL;
	background = load_image("GUI/InventoryBackground.png");
	apply_surface(backgroundX, backgroundY, background, screen);
	
	for (int32_t i = 0; i<inventorySize; i++)
	{
		if (objects[i] != NULL)
		{
			int itemX = i%columnCount;
			int itemY = i/columnCount;
			objects[i]->draw(backgroundX + itemX*objectSize+objectsStartOffsetX, backgroundY + itemY*objectSize+objectsStartOffsetY);
		}
	}	
	SDL_Surface* border = NULL;
	border = load_image("GUI/InventoryBackgroundRamen.png");
	apply_surface(SCREEN_WIDTH/2-282, SCREEN_HEIGHT/2-130, border, screen);

	if (draggingIndex != -1 && objects[draggingIndex] != NULL)
	{
		objects[draggingIndex]->drawDragging(mouseX, mouseY);
	}
}

void Inventory::update()
{
	if (!showInventory)
	{
		draggingIndex = -1;
	}
}

void Inventory::onMouseDown()
{
	int xRelativeToItems = mouseX - backgroundX - objectsStartOffsetX;
	int yRelativeToItems = mouseY - backgroundY - objectsStartOffsetY;

	if (xRelativeToItems < 0 || xRelativeToItems > columnCount*objectSize
		|| yRelativeToItems<0 || yRelativeToItems > rowCount*objectSize )
	{
		actionbar.onMouseDown();
		return;
	}

	draggingIndex = (yRelativeToItems/objectSize)*columnCount + xRelativeToItems/objectSize;
}

void Inventory::onMouseUp()
{
	if (draggingIndex == -1)
	{
		return;
	}

	int xRelativeToItems = mouseX - backgroundX - objectsStartOffsetX;
	int yRelativeToItems = mouseY - backgroundY - objectsStartOffsetY;

	if (xRelativeToItems < 0 || xRelativeToItems > columnCount*objectSize
		|| yRelativeToItems<0 || yRelativeToItems > rowCount*objectSize )
	{
		actionbar.onMouseUp();
		draggingIndex = -1;
		return;
	}

	int droppedIndex = (yRelativeToItems/objectSize)*columnCount + xRelativeToItems/objectSize;

	if (draggingIndex != droppedIndex)
		swap(draggingIndex, droppedIndex);

	draggingIndex = -1;
}

//TODO Draw Active (Fehlt logic)
	
