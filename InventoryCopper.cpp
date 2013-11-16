#include "main.h"
#include "InventoryCopper.h"
#include "FieldBackCopper.h"


InventoryCopper::InventoryCopper(void)
{
	init();
	amount = 1;
}

InventoryCopper::InventoryCopper(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCopper::~InventoryCopper(void)
{
}

void InventoryCopper::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackCopper* fieldBackCopper = new FieldBackCopper();
		fieldBackCopper->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryCopper::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Kupfer";

	imageActive = load_image("Background/Erze/Kupfer/Kupfer01.png");
	image = load_image("Background/Erze/Kupfer/Kupfer01.png");
}

