#include "CraftingRecipeTest.h"
#include "main.h"
#include "InventorySteelAxe.h"

CraftingRecipeTest::CraftingRecipeTest(void)
{
	name = "test" + to_string(rand());

	CraftingRecipeRequirement* reqEarth = new CraftingRecipeRequirement;
	reqEarth->name = "Erde";
	reqEarth->amount = 3;
	requirements.push_back(reqEarth);

	CraftingRecipeRequirement* reqCoal = new CraftingRecipeRequirement;
	reqCoal->name = "Kohle";
	reqCoal->amount = 2;
	requirements.push_back(reqCoal);
}


CraftingRecipeTest::~CraftingRecipeTest(void)
{
}

void CraftingRecipeTest::doCraft()
{
	if (canBeCrafted())
	{
		for (int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			InventorySteelAxe *inventorySteelAxe = new InventorySteelAxe;
			world.player.inventory.add(inventorySteelAxe);
		}
	}
}
