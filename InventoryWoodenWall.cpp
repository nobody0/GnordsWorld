#include "main.h"
#include "InventoryWoodenWall.h"



InventoryWoodenWall::InventoryWoodenWall(void)
{
	init();
	amount = 1;
}

InventoryWoodenWall::InventoryWoodenWall(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWoodenWall::~InventoryWoodenWall(void)
{
}

void InventoryWoodenWall::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		world.player.inventory.remove(this, 1);
	}
}

void InventoryWoodenWall::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Holzwand";

	//image = load_image("Inventar/Erze/Kupfer.png");
}

