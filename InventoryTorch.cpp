#include "main.h"
#include "InventoryTorch.h"


InventoryTorch::InventoryTorch(void)
{
	init();
	amount = 1;
}

InventoryTorch::InventoryTorch(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryTorch::~InventoryTorch(void)
{
}

void InventoryTorch::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryTorch::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Fackel";

	imageActive = load_image("Inventar/Werkzeug/Fackel.png");
	image = load_image("Inventar/Werkzeug/Fackel.png");
}

