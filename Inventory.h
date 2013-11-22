#pragma once

#include "InventoryObject.h"
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Actionbar.h"
#include "Rect.h"
#include "Crafting.h"

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	Actionbar actionbar;
	Crafting* crafting;

	int32_t inventorySize;
	InventoryObject** objects;
	
	int draggingIndex;

	int backgroundX;
	int backgroundY;
	int columnCount;
	int rowCount;
	
	int objectsStartOffsetX;
	int objectsStartOffsetY;

	int objectSize;

	bool add(InventoryObject* inventoryObject);

	bool remove(std::string name, int deltaAmount);

	bool remove(InventoryObject* object, int deltaAmount);

	bool remove(int index, int deltaAmount);

	bool hasObject(std::string name, int amount);

	void swap(int index1, int index2);

	void update();
	void draw();
	
	void onMouseDown();

	void onMouseUp();
};

