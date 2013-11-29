#pragma once
#include "craftingrecipe.h"

class CraftingRecipeRope :
	public CraftingRecipe
{
public:
	CraftingRecipeRope(void);
	~CraftingRecipeRope(void);

	void doCraft();
};

