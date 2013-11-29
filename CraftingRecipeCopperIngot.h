#pragma once
#include "craftingrecipe.h"

class CraftingRecipeCopperIngot :
	public CraftingRecipe
{
public:
	CraftingRecipeCopperIngot(void);
	~CraftingRecipeCopperIngot(void);

	void doCraft();
};

