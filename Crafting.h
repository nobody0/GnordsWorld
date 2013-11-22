#pragma once
#include <vector>
#include "CraftingRecipe.h"

class Crafting
{
public:
	Crafting(void);
	~Crafting(void);

	int craftingX;
	int craftingY;

	int listOffsetX;
	int listOffsetY;

	int activeOffsetX;
	int activeOffsetY;

	int craftingRecipeHeight;
	int craftingRecipeWidth;

	int activeRecipeIndex;
	int craftingListPage;
	unsigned int craftingListEntriesPerPage;
	std::vector<CraftingRecipe*> recipes;

	void draw();

	void onMouseDown();
};

