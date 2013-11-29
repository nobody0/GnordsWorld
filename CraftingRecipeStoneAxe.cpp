#include "CraftingRecipeStoneAxe.h"
#include "main.h"
#include "InventoryStoneAxe.h"

CraftingRecipeStoneAxe::CraftingRecipeStoneAxe(void)
{
	name = "Steinaxt";

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


CraftingRecipeStoneAxe::~CraftingRecipeStoneAxe(void)
{
}

void CraftingRecipeStoneAxe::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryStoneAxe *inventoryStoneAxe = new InventoryStoneAxe;
		world.player.inventory.add(inventoryStoneAxe);
	}
}