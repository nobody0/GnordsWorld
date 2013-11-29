#pragma once
#include "craftingrecipe.h"

class CraftingRecipeTorch :
	public CraftingRecipe
{
public:
	CraftingRecipeTorch(void);
	~CraftingRecipeTorch(void);

	void doCraft();
};

