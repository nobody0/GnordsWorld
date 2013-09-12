#pragma once
#include <string>
#include "SDL.h"
#include "Field.h"

class InventoryObject
{
public:
	int32_t amount;
	const SDL_Surface* image;
	const string name;

	InventoryObject(void);
	~InventoryObject(void);

	virtual void onUse(Field* target, const int32_t &x, const int32_t &y) = 0;
};

