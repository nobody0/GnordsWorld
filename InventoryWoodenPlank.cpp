#include "main.h"
#include "InventoryWoodenPlank.h"



InventoryWoodenPlank::InventoryWoodenPlank(void)
{
	init();
	amount = 1;
}

InventoryWoodenPlank::InventoryWoodenPlank(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWoodenPlank::~InventoryWoodenPlank(void)
{
}

void InventoryWoodenPlank::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryWoodenPlank::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Holzbrett";

	imageActive = load_image("Inventar/Holzbrett.png");
	image = load_image("Inventar/Holzbrett.png");
}

