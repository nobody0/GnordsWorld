#include "CraftingRecipeStick.h"
#include "main.h"
#include "InventoryStick.h"

CraftingRecipeStick::CraftingRecipeStick(void)
{
	name = "Stock";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Holz";
	req->amount = 1;
	requirements.push_back(req);

}

CraftingRecipeStick::~CraftingRecipeStick(void)
{
}

void CraftingRecipeStick::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryStick *inventoryStick = new InventoryStick;
		world.player.inventory.add(inventoryStick);
	}
}