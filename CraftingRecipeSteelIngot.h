#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSteelIngot :
	public CraftingRecipe
{
public:
	CraftingRecipeSteelIngot(void);
	~CraftingRecipeSteelIngot(void);

	void doCraft();
};
