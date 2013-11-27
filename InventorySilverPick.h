#pragma once
#include "inventoryobject.h"
class InventorySilverPick :
	public InventoryObject
{
public:
	InventorySilverPick(void);
	InventorySilverPick(int32_t amount);
	~InventorySilverPick(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};