#pragma once
#include "inventoryobject.h"
class InventorySilverSlice :
	public InventoryObject
{
public:
	InventorySilverSlice(void);
	InventorySilverSlice(int32_t amount);
	~InventorySilverSlice(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};