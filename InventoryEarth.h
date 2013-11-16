#pragma once
#include "inventoryobject.h"
class InventoryEarth :
	public InventoryObject
{
public:
	InventoryEarth(void);
	InventoryEarth(int32_t amount);
	~InventoryEarth(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};