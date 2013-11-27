#include "main.h"
#include "InventoryWood.h"


InventoryWood::InventoryWood(void)
{
	init();
	amount = 1;
}

InventoryWood::InventoryWood(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWood::~InventoryWood(void)
{
}

void InventoryWood::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryWood::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Eschenholz";

	image = load_image("Inventar/Holz/Eschenholz.png");
}

