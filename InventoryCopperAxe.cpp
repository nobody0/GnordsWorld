#include "main.h"
#include "InventoryCopperAxe.h"



InventoryCopperAxe::InventoryCopperAxe(void)
{
	init();
	amount = 1;
}

InventoryCopperAxe::InventoryCopperAxe(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCopperAxe::~InventoryCopperAxe(void)
{
}

void InventoryCopperAxe::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryCopperAxe::init()
{
	toolType = Default;
	toolLevel = 1.5;

	maxAmount = 1;
	name = "Kupferaxt";

	imageActive = load_image("Hand/Kupferaxt.png");
	image = load_image("Inventar/Werkzeug/Kupferaxt.png");
}

