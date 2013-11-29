#include "main.h"
#include "InventoryAlchemyTable.h"



InventoryAlchemyTable::InventoryAlchemyTable(void)
{
	init();
	amount = 1;
}

InventoryAlchemyTable::InventoryAlchemyTable(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryAlchemyTable::~InventoryAlchemyTable(void)
{
}

void InventoryAlchemyTable::onUse(Field* target, const int32_t &x, const int32_t &y)
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


void InventoryAlchemyTable::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Alchemietisch";

	imageActive = load_image("Inventar/Stationen/Alchemietisch.png");
	image = load_image("Inventar/Stationen/Alchemietisch.png");
}

