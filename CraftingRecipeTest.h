#pragma once
#include "craftingrecipe.h"

class CraftingRecipeTest :
	public CraftingRecipe
{
public:
	CraftingRecipeTest(void);
	~CraftingRecipeTest(void);

	void doCraft();
};

