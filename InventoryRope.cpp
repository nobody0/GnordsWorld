#include "main.h"
#include "InventoryRope.h"


InventoryRope::InventoryRope(void)
{
	init();
	amount = 1;
}

InventoryRope::InventoryRope(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryRope::~InventoryRope(void)
{
}

void InventoryRope::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryRope::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Seil";

	imageActive = load_image("Hand/Seil.png");
	image = load_image("Inventar/Werkzeug/Seil.png");
}

