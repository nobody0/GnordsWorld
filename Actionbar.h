#pragma once

#include "InventoryObject.h"
#include <string>
#include "SDL.h"

class Actionbar
{
public:
	Actionbar(void);
	~Actionbar(void);

	int actionbarSize;
	InventoryObject** barObjects;

	int actionbarX;
	int actionbarY;
	
	int objectsStartOffsetX;
	int objectsStartOffsetY;

	int objectSize;

	void add(InventoryObject* inventoryObject, int index);

	void remove(int index);

	void draw();
	
	void onMouseDown();

	void onMouseUp();
};

