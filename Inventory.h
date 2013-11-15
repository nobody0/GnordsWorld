#pragma once

#include "InventoryObject.h"
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	int32_t inventorySize;
	int toolBarSize;
	InventoryObject** objects;
	InventoryObject** toolBar;


	bool add(InventoryObject* inventoryObject);

	bool remove(std::string name, int deltaAmount);

	bool hasObject(std::string name, int amount);

	void update();
	void draw();
	void drawToolbar();
	
};

