#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSilverAxe :
	public CraftingRecipe
{
public:
	CraftingRecipeSilverAxe(void);
	~CraftingRecipeSilverAxe(void);

	void doCraft();
};

