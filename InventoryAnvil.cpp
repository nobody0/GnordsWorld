#include "main.h"
#include "InventoryAnvil.h"



InventoryAnvil::InventoryAnvil(void)
{
	init();
	amount = 1;
}

InventoryAnvil::InventoryAnvil(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryAnvil::~InventoryAnvil(void)
{
}

void InventoryAnvil::onUse(Field* target, const int32_t &x, const int32_t &y)
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


void InventoryAnvil::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Schmiede";

	imageActive = load_image("Inventar/Stationen/Schmiede.png");
	image = load_image("Inventar/Stationen/Schmiede.png");
}

