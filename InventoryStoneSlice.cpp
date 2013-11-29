#include "main.h"
#include "InventoryStoneSlice.h"



InventoryStoneSlice::InventoryStoneSlice(void)
{
	init();
	amount = 1;
}

InventoryStoneSlice::InventoryStoneSlice(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryStoneSlice::~InventoryStoneSlice(void)
{
}

void InventoryStoneSlice::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryStoneSlice::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Steinsichel";

	imageActive = load_image("Hand/Steinsichel.png");
	image = load_image("Inventar/Werkzeug/Steinsichel.png");
}

