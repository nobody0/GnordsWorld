#pragma once
#include "inventoryobject.h"
class InventorySteelPick :
	public InventoryObject
{
public:
	InventorySteelPick(void);
	InventorySteelPick(int32_t amount);
	~InventorySteelPick(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};