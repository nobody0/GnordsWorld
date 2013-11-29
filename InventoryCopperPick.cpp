#include "main.h"
#include "InventoryCopperPick.h"



InventoryCopperPick::InventoryCopperPick(void)
{
	init();
	amount = 1;
}

InventoryCopperPick::InventoryCopperPick(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCopperPick::~InventoryCopperPick(void)
{
}

void InventoryCopperPick::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryCopperPick::init()
{
	toolType = Default;
	toolLevel = 1.5;

	maxAmount = 1;
	name = "Kupferhacke";

	imageActive = load_image("Hand/Kupferhacke.png");
	image = load_image("Inventar/Werkzeug/Kupferhacke.png");
}

