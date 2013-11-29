#include "CraftingRecipeSilverSlice.h"
#include "main.h"
#include "InventorySilverSlice.h"

CraftingRecipeSilverSlice::CraftingRecipeSilverSlice(void)
{
	name = "SilberAxt";

	CraftingRecipeRequirement* req;

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Amboss";
	req->amount = 1;
	requirements.push_back(req);
	*/

	req = new CraftingRecipeRequirement;
	req->name = "Silberbarren";
	req->amount = 3;
	requirements.push_back(req);

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
}


CraftingRecipeSilverSlice::~CraftingRecipeSilverSlice(void)
{
}

void CraftingRecipeSilverSlice::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySilverSlice *inventorySilverSlice = new InventorySilverSlice;
		world.player.inventory.add(inventorySilverSlice);
	}
}