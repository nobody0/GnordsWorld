#pragma once
#include "inventoryobject.h"
class InventoryPumpkin :
	public InventoryObject
{
public:
	InventoryPumpkin(void);
	InventoryPumpkin(int32_t amount);
	~InventoryPumpkin(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};