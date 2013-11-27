#pragma once
#include "inventoryobject.h"
class InventoryAlchemyTable :
	public InventoryObject
{
public:
	InventoryAlchemyTable(void);
	InventoryAlchemyTable(int32_t amount);
	~InventoryAlchemyTable(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};