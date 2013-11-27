#include "main.h"
#include "InventoryWorkbanch.h"



InventoryWorkbanch::InventoryWorkbanch(void)
{
	init();
	amount = 1;
}

InventoryWorkbanch::InventoryWorkbanch(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWorkbanch::~InventoryWorkbanch(void)
{
}

void InventoryWorkbanch::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryWorkbanch::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Werkbank";

	image = load_image("Inventar/Stationen/Werkbank.png");
}

