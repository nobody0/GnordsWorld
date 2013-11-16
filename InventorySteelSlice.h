#pragma once
#include "inventoryobject.h"
class InventorySteelSlice :
	public InventoryObject
{
public:
	InventorySteelSlice(void);
	InventorySteelSlice(int32_t amount);
	~InventorySteelSlice(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};