#include "main.h"
#include "InventoryBucketFull.h"


InventoryBucketFull::InventoryBucketFull(void)
{
	init();
	amount = 1;
}

InventoryBucketFull::InventoryBucketFull(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryBucketFull::~InventoryBucketFull(void)
{
}

void InventoryBucketFull::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryBucketFull::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "EimerVoll";

	imageActive = load_image("Hand/EimerVoll.png");
	image = load_image("Inventar/Werkzeug/EimerVoll.png");
}

