#pragma once
#include "inventoryobject.h"
class InventoryCoal :
	public InventoryObject
{
public:
	InventoryCoal(void);
	InventoryCoal(int32_t amount);
	~InventoryCoal(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};