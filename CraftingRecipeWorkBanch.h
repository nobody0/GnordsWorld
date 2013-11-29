#pragma once
#include "craftingrecipe.h"

class CraftingRecipeWorkBanch :
	public CraftingRecipe
{
public:
	CraftingRecipeWorkBanch(void);
	~CraftingRecipeWorkBanch(void);

	void doCraft();
};

