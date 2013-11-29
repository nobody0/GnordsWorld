#pragma once
#include "craftingrecipe.h"

class CraftingRecipeWoodenPlank :
	public CraftingRecipe
{
public:
	CraftingRecipeWoodenPlank(void);
	~CraftingRecipeWoodenPlank(void);

	void doCraft();
};

