#pragma once
#include "inventoryobject.h"
class InventoryAnvil :
	public InventoryObject
{
public:
	InventoryAnvil(void);
	InventoryAnvil(int32_t amount);
	~InventoryAnvil(void);

	void init();

	//void onUse(Field* target, const int32_t &x, const int32_t &y);
};