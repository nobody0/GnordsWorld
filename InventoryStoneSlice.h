#pragma once
#include "inventoryobject.h"
class InventoryStoneSlice :
	public InventoryObject
{
public:
	InventoryStoneSlice(void);
	InventoryStoneSlice(int32_t amount);
	~InventoryStoneSlice(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};