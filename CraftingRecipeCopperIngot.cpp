#include "CraftingRecipeCopperIngot.h"
#include "main.h"
#include "InventoryCopperIngot.h"

CraftingRecipeCopperIngot::CraftingRecipeCopperIngot(void)
{
	name = "Kupferbarren";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Kupfer";
	req->amount = 2;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kohle";
	req->amount = 1;
	requirements.push_back(req);
}


CraftingRecipeCopperIngot::~CraftingRecipeCopperIngot(void)
{
}

void CraftingRecipeCopperIngot::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryCopperIngot *inventoryCopperIngot = new InventoryCopperIngot;
		world.player.inventory.add(inventoryCopperIngot);
	}
}
