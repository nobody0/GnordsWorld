#pragma once
#include "inventoryobject.h"
class InventoryWoodenWall :
	public InventoryObject
{
public:
	InventoryWoodenWall(void);
	InventoryWoodenWall(int32_t amount);
	~InventoryWoodenWall(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};