#pragma once
#include "inventoryobject.h"
class InventorySteelIngot :
	public InventoryObject
{
public:
	InventorySteelIngot(void);
	InventorySteelIngot(int32_t amount);
	~InventorySteelIngot(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};