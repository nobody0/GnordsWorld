#pragma once
#include "inventoryobject.h"
class InventoryCopperPick :
	public InventoryObject
{
public:
	InventoryCopperPick(void);
	InventoryCopperPick(int32_t amount);
	~InventoryCopperPick(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};