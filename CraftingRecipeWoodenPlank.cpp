#include "CraftingRecipeWoodenPlank.h"
#include "main.h"
#include "InventoryWoodenPlank.h"

CraftingRecipeWoodenPlank::CraftingRecipeWoodenPlank(void)
{
	name = "Holzbrett";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Holz";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kohle";
	req->amount = 2;
	requirements.push_back(req);
}


CraftingRecipeWoodenPlank::~CraftingRecipeWoodenPlank(void)
{
}

void CraftingRecipeWoodenPlank::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryWoodenPlank *inventoryWoodenPlank = new InventoryWoodenPlank(4);
		world.player.inventory.add(inventoryWoodenPlank);
	}
}