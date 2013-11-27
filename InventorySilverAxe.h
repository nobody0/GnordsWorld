#pragma once
#include "inventoryobject.h"
class InventorySilverAxe :
	public InventoryObject
{
public:
	InventorySilverAxe(void);
	InventorySilverAxe(int32_t amount);
	~InventorySilverAxe(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};