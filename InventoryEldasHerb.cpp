#include "main.h"
#include "InventoryEldasHerb.h"



InventoryEldasHerb::InventoryEldasHerb(void)
{
	init();
	amount = 1;
}

InventoryEldasHerb::InventoryEldasHerb(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryEldasHerb::~InventoryEldasHerb(void)
{
}

void InventoryEldasHerb::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryEldasHerb::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Eldaskraut";

	image = load_image("Inventar/Pflanzen/EldasKraut.png");
}

