#include "CraftingRecipeSteelPick.h"
#include "main.h"
#include "InventorySteelPick.h"

CraftingRecipeSteelPick::CraftingRecipeSteelPick(void)
{
	name = "Stahlaxt";

	CraftingRecipeRequirement* req;

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Amboss";
	req->amount = 1;
	requirements.push_back(req);
	*/

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Stock";
	req->amount = 1;
	requirements.push_back(req);
	*/

	/*
	req = new CraftingRecipeRequirement;
	req->name = "EimerVoll";
	req->amount = 1;
	requirements.push_back(req);
	*/

	req = new CraftingRecipeRequirement;
	req->name = "Stahlbarren";
	req->amount = 3;
	requirements.push_back(req);
}


CraftingRecipeSteelPick::~CraftingRecipeSteelPick(void)
{
}

void CraftingRecipeSteelPick::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySteelPick *inventorySteelPick = new InventorySteelPick;
		world.player.inventory.add(inventorySteelPick);
	}
}