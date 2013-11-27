#include "main.h"
#include "InventoryWoodenDoor.h"


InventoryWoodenDoor::InventoryWoodenDoor(void)
{
	init();
	amount = 1;
}

InventoryWoodenDoor::InventoryWoodenDoor(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWoodenDoor::~InventoryWoodenDoor(void)
{
}

void InventoryWoodenDoor::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryWoodenDoor::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Holztür";

	//image = load_image("Inventar/Holztür.png");
}

