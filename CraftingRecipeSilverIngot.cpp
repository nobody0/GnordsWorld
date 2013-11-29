#include "CraftingRecipeSilverIngot.h"
#include "main.h"
#include "InventorySilverIngot.h"

CraftingRecipeSilverIngot::CraftingRecipeSilverIngot(void)
{
	name = "Silberbarren";

	CraftingRecipeRequirement* req;

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Amboss";
	req->amount = 1;
	requirements.push_back(req);
	*/

	req = new CraftingRecipeRequirement;
	req->name = "Silber";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kohle";
	req->amount = 1;
	requirements.push_back(req);

	/*
	req = new CraftingRecipeRequirement;
	req->name = "EimerVoll";
	req->amount = 1;
	requirements.push_back(req);
	*/
}


CraftingRecipeSilverIngot::~CraftingRecipeSilverIngot(void)
{
}

void CraftingRecipeSilverIngot::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySilverIngot *inventorySilverIngot = new InventorySilverIngot;
		world.player.inventory.add(inventorySilverIngot);
	}
}