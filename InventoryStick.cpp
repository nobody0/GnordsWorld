#include "main.h"
#include "InventoryStick.h"



InventoryStick::InventoryStick(void)
{
	init();
	amount = 1;
}

InventoryStick::InventoryStick(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryStick::~InventoryStick(void)
{
}

void InventoryStick::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryStick::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Kupfer";

	image = load_image("Inventar/Holzstock.png");
}

