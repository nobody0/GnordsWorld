#pragma once
#include "craftingrecipe.h"

class CraftingRecipeStonePick :
	public CraftingRecipe
{
public:
	CraftingRecipeStonePick(void);
	~CraftingRecipeStonePick(void);

	void doCraft();
};

