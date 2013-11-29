#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSteelAxe :
	public CraftingRecipe
{
public:
	CraftingRecipeSteelAxe(void);
	~CraftingRecipeSteelAxe(void);

	void doCraft();
};

