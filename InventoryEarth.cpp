#include "main.h"
#include "InventoryEarth.h"
#include "FieldBackEarth.h"

InventoryEarth::InventoryEarth(void)
{
	init();
	amount = 1;
}

InventoryEarth::InventoryEarth(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryEarth::~InventoryEarth(void)
{
}

void InventoryEarth::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackEarth* fieldBackEarth = new FieldBackEarth();
		fieldBackEarth->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryEarth::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Erde";

	imageActive = load_image("Hand/Erde.png");
	image = load_image("Inventar/Erze/Erde.png");
}