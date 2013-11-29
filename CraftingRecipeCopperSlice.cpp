#include "CraftingRecipeCopperSlice.h"
#include "main.h"
#include "InventoryCopperSlice.h"

CraftingRecipeCopperSlice::CraftingRecipeCopperSlice(void)
{
	name = "Kupferbarren";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Werkbank";
	req->amount = 1;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kupfebarren";
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


CraftingRecipeCopperSlice::~CraftingRecipeCopperSlice(void)
{
}

void CraftingRecipeCopperSlice::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryCopperSlice *inventoryCopperSlice = new InventoryCopperSlice;
		world.player.inventory.add(inventoryCopperSlice);
	}
}