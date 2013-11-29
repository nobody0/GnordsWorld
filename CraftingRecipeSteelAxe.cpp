#include "CraftingRecipeSteelAxe.h"
#include "main.h"
#include "InventorySteelAxe.h"

CraftingRecipeSteelAxe::CraftingRecipeSteelAxe(void)
{
	name = "Stahlaxt";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Amboss";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Stock";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "EimerVoll";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Stahlbarren";
	req->amount = 4;
	requirements.push_back(req);
}


CraftingRecipeSteelAxe::~CraftingRecipeSteelAxe(void)
{
}

void CraftingRecipeSteelAxe::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySteelAxe *inventorySteelAxe = new InventorySteelAxe;
		world.player.inventory.add(inventorySteelAxe);
	}
}