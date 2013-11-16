#pragma once
#include "inventoryobject.h"
class InventoryStone :
	public InventoryObject
{
public:
	InventoryStone(void);
	InventoryStone(int32_t amount);
	~InventoryStone(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};