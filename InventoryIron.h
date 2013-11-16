#pragma once
#include "inventoryobject.h"
class InventoryIron :
	public InventoryObject
{
public:
	InventoryIron(void);
	InventoryIron(int32_t amount);
	~InventoryIron(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};