#include "main.h"
#include "InventoryBucketEmpty.h"


InventoryBucketEmpty::InventoryBucketEmpty(void)
{
	init();
	amount = 1;
}

InventoryBucketEmpty::InventoryBucketEmpty(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryBucketEmpty::~InventoryBucketEmpty(void)
{
}

void InventoryBucketEmpty::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryBucketEmpty::init()
{
	toolType = Bucket;
	toolLevel = 1;

	maxAmount = 99;
	name = "EimerLeer";

	imageActive = load_image("Hand/Eimer_leer.png");
	image = load_image("Inventar/Werkzeug/EimerLeer.png");
}

