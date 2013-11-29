#include "CraftingRecipeCopperAxe.h"
#include "main.h"
#include "InventoryCopperAxe.h"

CraftingRecipeCopperAxe::CraftingRecipeCopperAxe(void)
{
	name = "Kupferaxt";

	CraftingRecipeRequirement* reqWorkBanch = new CraftingRecipeRequirement;
	reqWorkBanch->name = "Werkbank";
	reqWorkBanch->amount = 1;
	requirements.push_back(reqWorkBanch);

	CraftingRecipeRequirement* reqCopperIngot = new CraftingRecipeRequirement;
	reqCopperIngot->name = "Kupferbarren";
	reqCopperIngot->amount = 4;
	requirements.push_back(reqCopperIngot);

	CraftingRecipeRequirement* reqStick = new CraftingRecipeRequirement;
	reqStick->name = "Stock";
	reqStick->amount = 1;
	requirements.push_back(reqStick);

	CraftingRecipeRequirement* reqRope = new CraftingRecipeRequirement;
	reqRope->name = "Seil";
	reqRope->amount = 1;
	requirements.push_back(reqRope);
}


CraftingRecipeCopperAxe::~CraftingRecipeCopperAxe(void)
{
}

void CraftingRecipeCopperAxe::doCraft()
{
	if (canBeCrafted())
	{
		for (int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryCopperAxe *inventoryCopperAxe = new InventoryCopperAxe;
		world.player.inventory.add(inventoryCopperAxe);
	}
}
