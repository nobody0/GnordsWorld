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
	//TODO: 2 Buttons zum erh�hen und reduzieren. Werden unter die Liste gesetzt und in MouseDown behandelt. Nicht nutzbare buttons ausblenden.(Vectorl�nge / entries per page ergibt die seiten.
	unsigned int craftingListEntriesPerPage;
	std::vector<CraftingRecipe*> recipes;
	

	void draw();

	void onMouseDown();
	//TODO Craftbutton gedr�ckt ermitteln. Aktive craften
};

