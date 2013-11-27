#pragma once
#include "inventoryobject.h"
class InventoryStonePick :
	public InventoryObject
{
public:
	InventoryStonePick(void);
	InventoryStonePick(int32_t amount);
	~InventoryStonePick(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};