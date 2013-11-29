#include "CraftingRecipeSilverPick.h"
#include "main.h"
#include "InventorySilverPick.h"

CraftingRecipeSilverPick::CraftingRecipeSilverPick(void)
{
	name = "Silberhacke";

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
}


CraftingRecipeSilverPick::~CraftingRecipeSilverPick(void)
{
}

void CraftingRecipeSilverPick::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySilverPick *inventorySilverPick = new InventorySilverPick;
		world.player.inventory.add(inventorySilverPick);
	}
}