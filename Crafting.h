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

	int craftingButtonOffsetX;
	int craftingButtonOffsetY;

	int craftingButtonHeight;
	int craftingButtonWidth;

	int craftingRecipeHeight;
	int craftingRecipeWidth;

	int activeRecipeIndex;
	int craftingListPage;

	int pagginationXButtonLeft;
	int pagginationXButtonRight;
	int pagginationYButton;

	int craftingListEntriesPerPage;
	std::vector<CraftingRecipe*> recipes;

	int craftingListPages;

	void setScreenSize();

	void draw();

	void onMouseDown();
};

