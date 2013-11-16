#pragma once
#include "inventoryobject.h"
class InventorySteelAxe :
	public InventoryObject
{
public:
	InventorySteelAxe(void);
	InventorySteelAxe(int32_t amount);
	~InventorySteelAxe(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};