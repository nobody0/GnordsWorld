#include "CraftingRecipeAnvil.h"
#include "main.h"
#include "InventoryAnvil.h"

CraftingRecipeAnvil::CraftingRecipeAnvil(void)
{
	name = "Amboss";

	CraftingRecipeRequirement* reqWood = new CraftingRecipeRequirement;
	reqWood->name = "Holz";
	reqWood->amount = 20;
	requirements.push_back(reqWood);

	
}


CraftingRecipeAnvil::~CraftingRecipeAnvil(void)
{
}

void CraftingRecipeAnvil::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryAnvil *inventoryAnvil = new InventoryAnvil;
		world.player.inventory.add(inventoryAnvil);
	}
}
