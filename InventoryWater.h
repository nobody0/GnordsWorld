#pragma once
#include "inventoryobject.h"
class InventoryWater :
	public InventoryObject
{
public:
	InventoryWater(void);
	InventoryWater(int32_t amount);
	~InventoryWater(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};

