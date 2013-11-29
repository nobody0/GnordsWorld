#include "CraftingRecipeAlchemyTable.h"
#include "main.h"
#include "InventoryAlchemyTable.h"

CraftingRecipeAlchemyTable::CraftingRecipeAlchemyTable(void)
{
	name = "Alchemietisch";

	/*
	CraftingRecipeRequirement* reqWoodenPlank = new CraftingRecipeRequirement;
	reqWoodenPlank->name = "Holzbrett";
	reqWoodenPlank->amount = 5;
	requirements.push_back(reqWoodenPlank);
	*/

	/*
	CraftingRecipeRequirement* reqStick = new CraftingRecipeRequirement;
	reqStick->name = "Stock";
	reqStick->amount = 2;
	requirements.push_back(reqStick);
	*/

	CraftingRecipeRequirement* reqSteelIngot = new CraftingRecipeRequirement;
	reqSteelIngot->name = "Stahlbarren";
	reqSteelIngot->amount = 2;
	requirements.push_back(reqSteelIngot);

	/*
	CraftingRecipeRequirement* reqRope = new CraftingRecipeRequirement;
	reqRope->name = "Seil";
	reqRope->amount = 1;
	requirements.push_back(reqRope);
	*/

	CraftingRecipeRequirement* reqBucketFull = new CraftingRecipeRequirement;
	reqBucketFull->name = "EimerVoll";
	reqBucketFull->amount = 2;
	requirements.push_back(reqBucketFull);
}


CraftingRecipeAlchemyTable::~CraftingRecipeAlchemyTable(void)
{
}

void CraftingRecipeAlchemyTable::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryAlchemyTable *inventoryAlchemyTable = new InventoryAlchemyTable;
		world.player.inventory.add(inventoryAlchemyTable);
	}
}
