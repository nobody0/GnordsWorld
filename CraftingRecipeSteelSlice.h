#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSteelSlice :
	public CraftingRecipe
{
public:
	CraftingRecipeSteelSlice(void);
	~CraftingRecipeSteelSlice(void);

	void doCraft();
};

