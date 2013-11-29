#include "CraftingRecipeSteelSlice.h"
#include "main.h"
#include "InventorySteelSlice.h"

CraftingRecipeSteelSlice::CraftingRecipeSteelSlice(void)
{
	name = "Stahlsichel";

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


CraftingRecipeSteelSlice::~CraftingRecipeSteelSlice(void)
{
}

void CraftingRecipeSteelSlice::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySteelSlice *inventorySteelSlice = new InventorySteelSlice;
		world.player.inventory.add(inventorySteelSlice);
	}
}