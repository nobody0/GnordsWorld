#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSilverPick :
	public CraftingRecipe
{
public:
	CraftingRecipeSilverPick(void);
	~CraftingRecipeSilverPick(void);

	void doCraft();
};

