#include "CraftingRecipeMetalBucket.h"
#include "main.h"
#include "InventoryBucketEmpty.h"

CraftingRecipeMetalBucket::CraftingRecipeMetalBucket(void)
{
	name = "Eimer";

	CraftingRecipeRequirement* req;

	req = new CraftingRecipeRequirement;
	req->name = "Stahlbarren";
	req->amount = 5;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kupferbarren";
	req->amount = 2;
	requirements.push_back(req);

	req = new CraftingRecipeRequirement;
	req->name = "Kupferbarren";
	req->amount = 2;
	requirements.push_back(req);
}


CraftingRecipeMetalBucket::~CraftingRecipeMetalBucket(void)
{
}

void CraftingRecipeMetalBucket::doCraft()
{
	if (canBeCrafted())
	{
		for (unsigned int i = 0; i < requirements.size(); i++)
		{
			world.player.inventory.remove(requirements[i]->name, requirements[i]->amount);	
			
		}
		InventoryBucketEmpty *inventoryBucketEmpty = new InventoryBucketEmpty;
		world.player.inventory.add(inventoryBucketEmpty);
	}
}