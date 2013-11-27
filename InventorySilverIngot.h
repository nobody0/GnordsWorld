#pragma once
#include "inventoryobject.h"
class InventorySilverIngot :
	public InventoryObject
{
public:
	InventorySilverIngot(void);
	InventorySilverIngot(int32_t amount);
	~InventorySilverIngot(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};