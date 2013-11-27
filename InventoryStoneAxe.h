#pragma once
#include "inventoryobject.h"
class InventoryStoneAxe :
	public InventoryObject
{
public:
	InventoryStoneAxe(void);
	InventoryStoneAxe(int32_t amount);
	~InventoryStoneAxe(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};