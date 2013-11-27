#pragma once
#include "inventoryobject.h"
class InventoryCopperIngot :
	public InventoryObject
{
public:
	InventoryCopperIngot(void);
	InventoryCopperIngot(int32_t amount);
	~InventoryCopperIngot(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};