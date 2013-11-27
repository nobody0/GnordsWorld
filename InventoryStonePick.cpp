#include "main.h"
#include "InventoryStonePick.h"



InventoryStonePick::InventoryStonePick(void)
{
	init();
	amount = 1;
}

InventoryStonePick::InventoryStonePick(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryStonePick::~InventoryStonePick(void)
{
}

void InventoryStonePick::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryStonePick::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Steinhacke";

	imageActive = load_image("Hand/Steinhacke.png");
	image = load_image("Inventar/Werkzeug/Steinhacke.png");
}

