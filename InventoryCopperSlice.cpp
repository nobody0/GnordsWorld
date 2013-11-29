#include "main.h"
#include "InventoryCopperSlice.h"


InventoryCopperSlice::InventoryCopperSlice(void)
{
	init();
	amount = 1;
}

InventoryCopperSlice::InventoryCopperSlice(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCopperSlice::~InventoryCopperSlice(void)
{
}

void InventoryCopperSlice::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryCopperSlice::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Kupfersichel";

	imageActive = load_image("Hand/Kupfersichel.png");
	image = load_image("Inventar/Werkzeug/Kupfersichel.png");
}

