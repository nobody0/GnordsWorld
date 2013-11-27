#pragma once
#include "inventoryobject.h"
class InventoryWoodenDoor :
	public InventoryObject
{
public:
	InventoryWoodenDoor(void);
	InventoryWoodenDoor(int32_t amount);
	~InventoryWoodenDoor(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};