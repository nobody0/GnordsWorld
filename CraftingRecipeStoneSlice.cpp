#include "CraftingRecipeStoneSlice.h"
#include "main.h"
#include "InventoryStoneSlice.h"

CraftingRecipeStoneSlice::CraftingRecipeStoneSlice(void)
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


CraftingRecipeStoneSlice::~CraftingRecipeStoneSlice(void)
{
}

void CraftingRecipeStoneSlice::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryStoneSlice *inventoryStoneSlice = new InventoryStoneSlice;
		world.player.inventory.add(inventoryStoneSlice);
	}
}