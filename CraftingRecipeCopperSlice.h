#pragma once
#include "craftingrecipe.h"

class CraftingRecipeCopperSlice :
	public CraftingRecipe

{
public:
	CraftingRecipeCopperSlice(void);
	~CraftingRecipeCopperSlice(void);

	void doCraft();
};

