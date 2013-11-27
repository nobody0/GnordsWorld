#pragma once
#include "inventoryobject.h"
class InventoryStick :
	public InventoryObject
{
public:
	InventoryStick(void);
	InventoryStick(int32_t amount);
	~InventoryStick(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};