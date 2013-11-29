#pragma once
#include "craftingrecipe.h"

class CraftingRecipeStoneSlice :
	public CraftingRecipe
{
public:
	CraftingRecipeStoneSlice(void);
	~CraftingRecipeStoneSlice(void);

	void doCraft();
};

