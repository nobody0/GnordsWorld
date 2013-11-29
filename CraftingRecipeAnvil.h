#pragma once
#include "craftingrecipe.h"

class CraftingRecipeAnvil :
	public CraftingRecipe
{
public:
	CraftingRecipeAnvil(void);
	~CraftingRecipeAnvil(void);

	void doCraft();
};

