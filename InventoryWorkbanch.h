#pragma once
#include "inventoryobject.h"
class InventoryWorkbanch :
	public InventoryObject
{
public:
	InventoryWorkbanch(void);
	InventoryWorkbanch(int32_t amount);
	~InventoryWorkbanch(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};