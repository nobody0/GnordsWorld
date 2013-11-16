#pragma once
#include "inventoryobject.h"
class InventoryCopper :
	public InventoryObject
{
public:
	InventoryCopper(void);
	InventoryCopper(int32_t amount);
	~InventoryCopper(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};