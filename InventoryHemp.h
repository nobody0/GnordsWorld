#pragma once
#include "inventoryobject.h"
class InventoryHemp :
	public InventoryObject
{
public:
	InventoryHemp(void);
	InventoryHemp(int32_t amount);
	~InventoryHemp(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};