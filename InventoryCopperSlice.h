#pragma once
#include "inventoryobject.h"
class InventoryCopperSlice :
	public InventoryObject
{
public:
	InventoryCopperSlice(void);
	InventoryCopperSlice(int32_t amount);
	~InventoryCopperSlice(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};