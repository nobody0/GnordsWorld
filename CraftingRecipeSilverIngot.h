#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSilverIngot :
	public CraftingRecipe
{
public:
	CraftingRecipeSilverIngot(void);
	~CraftingRecipeSilverIngot(void);

	void doCraft();
};

