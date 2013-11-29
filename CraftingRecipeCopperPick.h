#pragma once
#include "craftingrecipe.h"

class CraftingRecipeCopperPick :
	public CraftingRecipe
{
public:
	CraftingRecipeCopperPick(void);
	~CraftingRecipeCopperPick(void);

	void doCraft();
};

