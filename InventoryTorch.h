#pragma once
#include "inventoryobject.h"
class InventoryTorch :
	public InventoryObject
{
public:
	InventoryTorch(void);
	InventoryTorch(int32_t amount);
	~InventoryTorch(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};