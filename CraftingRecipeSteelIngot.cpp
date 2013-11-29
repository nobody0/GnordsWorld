#include "CraftingRecipeSteelIngot.h"
#include "main.h"
#include "InventorySteelIngot.h"

CraftingRecipeSteelIngot::CraftingRecipeSteelIngot(void)
{
	name = "Stahlbarren";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Eisen";
	req->amount = 2;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kohle";
	req->amount = 1;
	requirements.push_back(req);

}

CraftingRecipeSteelIngot::~CraftingRecipeSteelIngot(void)
{
}

void CraftingRecipeSteelIngot::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventorySteelIngot *inventorySteelIngot = new InventorySteelIngot;
		world.player.inventory.add(inventorySteelIngot);
	}
}