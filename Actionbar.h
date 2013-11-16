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


	void add(InventoryObject* inventoryObject, int index);

	void remove(int index);

	void draw();
};

