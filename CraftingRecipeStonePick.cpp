#include "CraftingRecipeStonePick.h"
#include "main.h"
#include "InventoryStonePick.h"

CraftingRecipeStonePick::CraftingRecipeStonePick(void)
{
	name = "Steinhacke";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Stein";
	req->amount = 4;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Stock";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Seil";
	req->amount = 1;
	requirements.push_back(req);
}


CraftingRecipeStonePick::~CraftingRecipeStonePick(void)
{
}

void CraftingRecipeStonePick::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryStonePick *inventoryStonePick = new InventoryStonePick;
		world.player.inventory.add(inventoryStonePick);
	}
}