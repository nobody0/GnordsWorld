#include "CraftingRecipeSilverAxe.h"
#include "main.h"
#include "InventorySilverAxe.h"

CraftingRecipeSilverAxe::CraftingRecipeSilverAxe(void)
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


CraftingRecipeSilverAxe::~CraftingRecipeSilverAxe(void)
{
}

void CraftingRecipeSilverAxe::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySilverAxe *inventorySilverAxe = new InventorySilverAxe;
		world.player.inventory.add(inventorySilverAxe);
	}
}