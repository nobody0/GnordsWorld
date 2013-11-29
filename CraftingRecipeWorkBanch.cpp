#include "CraftingRecipeWorkBanch.h"
#include "main.h"
#include "InventoryWorkbanch.h"

CraftingRecipeWorkBanch::CraftingRecipeWorkBanch(void)
{
	name = "Werkbank";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Holz";
	req->amount = 20;
	requirements.push_back(req);
}


CraftingRecipeWorkBanch::~CraftingRecipeWorkBanch(void)
{
}

void CraftingRecipeWorkBanch::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryWorkbanch* inventoryWorkBanch = new InventoryWorkbanch;
		world.player.inventory.add(inventoryWorkBanch);
	}
}