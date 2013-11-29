#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSilverSlice :
	public CraftingRecipe
{
public:
	CraftingRecipeSilverSlice(void);
	~CraftingRecipeSilverSlice(void);

	void doCraft();
};

