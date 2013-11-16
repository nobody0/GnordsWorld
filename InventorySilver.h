#pragma once
#include "inventoryobject.h"
class InventorySilver :
	public InventoryObject
{
public:
	InventorySilver(void);
	InventorySilver(int32_t amount);
	~InventorySilver(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};