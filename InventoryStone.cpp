#include "main.h"
#include "InventoryStone.h"
#include "FieldBackStone.h"


InventoryStone::InventoryStone(void)
{
	init();
	amount = 1;
}

InventoryStone::InventoryStone(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryStone::~InventoryStone(void)
{
}

void InventoryStone::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackStone* fieldBackStone = new FieldBackStone();
		fieldBackStone->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryStone::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Steine";

	imageActive = load_image("Background/Erze/Steine/Steine01.png");
	image = load_image("Background/Erze/Steine/Steine01.png");
}

