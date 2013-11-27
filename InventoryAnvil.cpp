#include "main.h"
#include "InventoryAnvil.h"



InventoryAnvil::InventoryAnvil(void)
{
	init();
	amount = 1;
}

InventoryAnvil::InventoryAnvil(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryAnvil::~InventoryAnvil(void)
{
}
//TODO
/*
void InventoryAlchemyTable::onUse(Field* target, const int32_t &x, const int32_t &y)
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
*/

void InventoryAnvil::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Schmiede";

	
	image = load_image("Inventar/Stationen/Schmiede.png");
}

