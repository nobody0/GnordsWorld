#pragma once
#include "inventoryobject.h"
class InventoryWoodenPlank :
	public InventoryObject
{
public:
	InventoryWoodenPlank(void);
	InventoryWoodenPlank(int32_t amount);
	~InventoryWoodenPlank(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};