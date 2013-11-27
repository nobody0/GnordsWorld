#include "main.h"
#include "InventorySilverSlice.h"



InventorySilverSlice::InventorySilverSlice(void)
{
	init();
	amount = 1;
}

InventorySilverSlice::InventorySilverSlice(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySilverSlice::~InventorySilverSlice(void)
{
}

void InventorySilverSlice::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventorySilverSlice::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Silbersichel";

	imageActive = load_image("Hand/Silbersichel.png");
	image = load_image("Inventar/Werkzeug/Silbersichel.png");
}

