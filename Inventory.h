#pragma once

#include "InventoryObject.h"
#include <string>

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
	//True wenn erfolgreich entfernt.
	//Bein null aus inventar Toolbar und active tool löschen. Darf nicht unter null
	bool hasObject(std::string name, int amount);

	void update();
	void draw();
	
};

