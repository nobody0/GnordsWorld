#include "CraftingRecipeTorch.h"
#include "main.h"
#include "InventoryTorch.h"

CraftingRecipeTorch::CraftingRecipeTorch(void)
{
	name = "Fackel";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Stock";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kohle";
	req->amount = 1;
	requirements.push_back(req);
}

CraftingRecipeTorch::~CraftingRecipeTorch(void)
{
}

void CraftingRecipeTorch::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryTorch *inventoryTorch = new InventoryTorch;
		world.player.inventory.add(inventoryTorch);
	}
}