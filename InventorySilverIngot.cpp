#include "main.h"
#include "InventorySilverIngot.h"


InventorySilverIngot::InventorySilverIngot(void)
{
	init();
	amount = 1;
}

InventorySilverIngot::InventorySilverIngot(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySilverIngot::~InventorySilverIngot(void)
{
}

void InventorySilverIngot::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventorySilverIngot::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Silberbarren";

	image = load_image("Inventar/Barren/Silberbarren.png");
}

