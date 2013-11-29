#include "main.h"
#include "InventorySilverPick.h"


InventorySilverPick::InventorySilverPick(void)
{
	init();
	amount = 1;
}

InventorySilverPick::InventorySilverPick(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySilverPick::~InventorySilverPick(void)
{
}

void InventorySilverPick::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventorySilverPick::init()
{
	toolType = Default;
	toolLevel = 3.5;

	maxAmount = 1;
	name = "Silberhacke";

	imageActive = load_image("Hand/Silberhacke.png");
	image = load_image("Inventar/Werkzeug/Silberhacke.png");
}

