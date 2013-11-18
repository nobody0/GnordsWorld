#include "main.h"
#include "InventoryCoal.h"
#include "FieldBackCoal.h"


InventoryCoal::InventoryCoal(void)
{
	init();
	amount = 1;
}

InventoryCoal::InventoryCoal(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryCoal::~InventoryCoal(void)
{
}

void InventoryCoal::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackCoal* fieldBackCoal = new FieldBackCoal();
		fieldBackCoal->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventoryCoal::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Kohle";

	imageActive = load_image("Hand/Kohle.png");
	image = load_image("Inventar/Erze/Kohle.png");
}

