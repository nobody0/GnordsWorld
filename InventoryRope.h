#pragma once
#include "inventoryobject.h"
class InventoryRope :
	public InventoryObject
{
public:
	InventoryRope(void);
	InventoryRope(int32_t amount);
	~InventoryRope(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};