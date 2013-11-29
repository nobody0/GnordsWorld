#pragma once
#include "craftingrecipe.h"

class CraftingRecipeMetalBucket :
	public CraftingRecipe
{
public:
	CraftingRecipeMetalBucket(void);
	~CraftingRecipeMetalBucket(void);

	void doCraft();
};

