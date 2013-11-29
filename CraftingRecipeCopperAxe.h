#pragma once
#include "craftingrecipe.h"

class CraftingRecipeCopperAxe :
	public CraftingRecipe
{
public:
	CraftingRecipeCopperAxe(void);
	~CraftingRecipeCopperAxe(void);

	void doCraft();
};

