#pragma once
#include "inventoryobject.h"
class InventoryEldasHerb :
	public InventoryObject
{
public:
	InventoryEldasHerb(void);
	InventoryEldasHerb(int32_t amount);
	~InventoryEldasHerb(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};