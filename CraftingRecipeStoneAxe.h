#pragma once
#include "craftingrecipe.h"

class CraftingRecipeStoneAxe :
	public CraftingRecipe
{
public:
	CraftingRecipeStoneAxe(void);
	~CraftingRecipeStoneAxe(void);

	void doCraft();
};

