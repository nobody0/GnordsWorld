#pragma once
#include <string>
#include "SDL.h"
#include "Field.h"
#include "ToolTypes.h"

class InventoryObject
{
public:
	int32_t amount;
	int maxAmount;

	SDL_Surface* image;
	SDL_Surface* imageActive;

	string name;

	ToolTypes toolType;
	int32_t toolLevel;

	InventoryObject(void);
	~InventoryObject(void);

	virtual void onUse(Field* target, const int32_t &x, const int32_t &y);

	//virtual void draw(int x, int y);
	virtual void drawActive(int x, int y);
};

