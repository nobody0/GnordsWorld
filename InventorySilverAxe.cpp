#include "main.h"
#include "InventorySilverAxe.h"



InventorySilverAxe::InventorySilverAxe(void)
{
	init();
	amount = 1;
}

InventorySilverAxe::InventorySilverAxe(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySilverAxe::~InventorySilverAxe(void)
{
}

void InventorySilverAxe::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventorySilverAxe::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "silberaxt";

	imageActive = load_image("Hand/Silberaxt.png");
	image = load_image("Inventar/Werkzeug/Silberaxt.png");
}

