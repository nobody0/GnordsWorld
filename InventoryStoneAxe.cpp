#include "main.h"
#include "InventoryStoneAxe.h"



InventoryStoneAxe::InventoryStoneAxe(void)
{
	init();
	amount = 1;
}

InventoryStoneAxe::InventoryStoneAxe(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryStoneAxe::~InventoryStoneAxe(void)
{
}

void InventoryStoneAxe::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryStoneAxe::init()
{
	toolType = Default;
	toolLevel = 2;

	maxAmount = 1;
	name = "Steinaxt";

	imageActive = load_image("Hand/Steinaxt.png");
	image = load_image("Inventar/Werkzeug/Steinaxt.png");
}

