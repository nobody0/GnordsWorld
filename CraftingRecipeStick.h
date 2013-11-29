#pragma once
#include "craftingrecipe.h"

class CraftingRecipeStick :
	public CraftingRecipe
{
public:
	CraftingRecipeStick(void);
	~CraftingRecipeStick(void);

	void doCraft();
};

