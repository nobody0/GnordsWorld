#pragma once
#include <string>

class CraftingRecipeRequirement
{
public:
	CraftingRecipeRequirement(void);
	~CraftingRecipeRequirement(void);

	std::string name;
	int amount;
};

