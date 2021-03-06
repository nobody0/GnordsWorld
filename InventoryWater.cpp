#include "main.h"
#include "InventoryWater.h"
#include "FieldBackWater.h"

InventoryWater::InventoryWater(void)
{
	init();
	amount = 1;
}

InventoryWater::InventoryWater(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryWater::~InventoryWater(void)
{
}

void InventoryWater::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackWater* fieldBackWater = new FieldBackWater();
		fieldBackWater->init(x*GRID_SIZE, y*GRID_SIZE);

		fieldBackWater->setWaterLevel(fieldBackWater->maxWaterLevel);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryWater::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Wasser";

	imageActive = load_image("Hand/Eimer_voll.png");
	image = load_image("Inventar/Werkzeug/EimerVoll.png");
}
