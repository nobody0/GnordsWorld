#include "CraftingRecipeRope.h"
#include "main.h"
#include "InventoryRope.h"

CraftingRecipeRope::CraftingRecipeRope(void)
{
	name = "Seil";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Hanf";
	req->amount = 1;
	requirements.push_back(req);
}


CraftingRecipeRope::~CraftingRecipeRope(void)
{
}

void CraftingRecipeRope::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryRope *inventoryRope = new InventoryRope(2);
		world.player.inventory.add(inventoryRope);
	}
}