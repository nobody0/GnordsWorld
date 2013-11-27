#pragma once
#include "inventoryobject.h"
class InventoryCopperAxe :
	public InventoryObject
{
public:
	InventoryCopperAxe(void);
	InventoryCopperAxe(int32_t amount);
	~InventoryCopperAxe(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};