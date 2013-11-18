#include "main.h"
#include "InventoryIron.h"
#include "FieldBackIron.h"


InventoryIron::InventoryIron(void)
{
	init();
	amount = 1;
}

InventoryIron::InventoryIron(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryIron::~InventoryIron(void)
{
}

void InventoryIron::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackIron* fieldBackIron = new FieldBackIron();
		fieldBackIron->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryIron::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Eisen";

	imageActive = load_image("Hand/Eisen.png");
	image = load_image("Inventar/Erze/Eisen.png");
}

