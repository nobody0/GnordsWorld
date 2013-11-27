#include "main.h"
#include "InventoryCopperIngot.h"


InventoryCopperIngot::InventoryCopperIngot(void)
{
	init();
	amount = 1;
}

InventoryCopperIngot::InventoryCopperIngot(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCopperIngot::~InventoryCopperIngot(void)
{
}

void InventoryCopperIngot::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryCopperIngot::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Kupferbarren";

	imageActive = load_image("Hand/Kupferbarren.png");
	image = load_image("Inventar/Barren/Kupferbarren.png");
}

