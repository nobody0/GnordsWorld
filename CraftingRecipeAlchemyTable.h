#pragma once
#include "craftingrecipe.h"

class CraftingRecipeAlchemyTable :
	public CraftingRecipe
{
public:
	CraftingRecipeAlchemyTable(void);
	~CraftingRecipeAlchemyTable(void);

	void doCraft();
};

