#include "CraftingRecipeCopperPick.h"
#include "main.h"
#include "InventoryCopperPick.h"

CraftingRecipeCopperPick::CraftingRecipeCopperPick(void)
{
	name = "Kupferhacke";

	CraftingRecipeRequirement* req;

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Werkbank";
	req->amount = 1;
	requirements.push_back(req);
	*/
	
	req = new CraftingRecipeRequirement;
	req->name = "Kupferbarren";
	req->amount = 3;
	requirements.push_back(req);

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Stock";
	req->amount = 1;
	requirements.push_back(req);
	*/

	/*
	req = new CraftingRecipeRequirement;
	req->name = "Seil";
	req->amount = 1;
	requirements.push_back(req);
	*/
}


CraftingRecipeCopperPick::~CraftingRecipeCopperPick(void)
{
}

void CraftingRecipeCopperPick::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryCopperPick *inventoryCopperPick = new InventoryCopperPick;
		world.player.inventory.add(inventoryCopperPick);
	}
}
