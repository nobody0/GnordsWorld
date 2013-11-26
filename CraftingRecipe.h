#pragma once

#include <vector>
#include <string>
#include "SDL.h"
#include "CraftingRecipeRequirement.h"

class CraftingRecipe
{
public:
	CraftingRecipe(void);
	~CraftingRecipe(void);

	std::string name;

	std::vector<CraftingRecipeRequirement*> requirements;

	void draw(int x, int y);
	void drawActive(int x, int y);
	//TODO Alle requirements mit aufschreiben, Craftbutten mit drawen
	bool canBeCrafted();
	
	virtual void doCraft() = 0;
	//TODO Muss implementiert werden
};

