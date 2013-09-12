#pragma once
#include "InventoryObject.h"

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	int32_t inventorySize;
	InventoryObject** objects;

	bool add(InventoryObject* inventoryObject);
};

