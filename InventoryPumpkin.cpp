#include "main.h"
#include "InventoryPumpkin.h"


InventoryPumpkin::InventoryPumpkin(void)
{
	init();
	amount = 1;
}

InventoryPumpkin::InventoryPumpkin(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryPumpkin::~InventoryPumpkin(void)
{
}

void InventoryPumpkin::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryPumpkin::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Kürbis";

	imageActive = load_image("Inventar/Werkzeug/Kürbis.png");
	image = load_image("Inventar/Werkzeug/Kürbis.png");
}

