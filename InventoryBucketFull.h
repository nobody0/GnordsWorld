#pragma once
#include "inventoryobject.h"
class InventoryBucketFull :
	public InventoryObject
{
public:
	InventoryBucketFull(void);
	InventoryBucketFull(int32_t amount);
	~InventoryBucketFull(void);

	void init();

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};