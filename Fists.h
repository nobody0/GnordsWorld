#pragma once
#include "InventoryObject.h"

class Fists :
	public InventoryObject
{
public:
	Fists(void);
	~Fists(void);

	void onUse(Field* target, const int32_t &x, const int32_t &y);
};

