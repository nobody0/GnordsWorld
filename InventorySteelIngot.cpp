#include "main.h"
#include "InventorySteelIngot.h"



InventorySteelIngot::InventorySteelIngot(void)
{
	init();
	amount = 1;
}

InventorySteelIngot::InventorySteelIngot(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySteelIngot::~InventorySteelIngot(void)
{
}

void InventorySteelIngot::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventorySteelIngot::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Stahlbarren";

	image = load_image("Inventar/Barren/Stahlbarren.png");
}

