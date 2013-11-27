#pragma once
#include "inventoryobject.h"
class InventoryBucketEmpty :
	public InventoryObject
{
public:
	InventoryBucketEmpty(void);
	InventoryBucketEmpty(int32_t amount);
	~InventoryBucketEmpty(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};