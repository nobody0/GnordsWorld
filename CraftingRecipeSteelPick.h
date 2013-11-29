#pragma once
#include "craftingrecipe.h"

class CraftingRecipeSteelPick :
	public CraftingRecipe
{
public:
	CraftingRecipeSteelPick(void);
	~CraftingRecipeSteelPick(void);

	void doCraft();
};

