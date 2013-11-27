#include "main.h"
#include "InventoryHemp.h"


InventoryHemp::InventoryHemp(void)
{
	init();
	amount = 1;
}

InventoryHemp::InventoryHemp(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryHemp::~InventoryHemp(void)
{
}

void InventoryHemp::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryHemp::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Hanf";

	image = load_image("Inventar/Pflanzen/Hanf.png");
}

