#pragma once
#include "inventoryobject.h"
class InventoryWood :
	public InventoryObject
{
public:
	InventoryWood(void);
	InventoryWood(int32_t amount);
	~InventoryWood(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};