#include "main.h"
#include "InventoryDirektHealingPotion.h"



InventoryDirektHealingPotion::InventoryDirektHealingPotion(void)
{
	init();
	amount = 1;
}

InventoryDirektHealingPotion::InventoryDirektHealingPotion(int32_t amount)
{
	init();
	this->amount = amount;
}


InventoryDirektHealingPotion::~InventoryDirektHealingPotion(void)
{
}

void InventoryDirektHealingPotion::onUse(Field* target, const int32_t &x, const int32_t &y)
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

void InventoryDirektHealingPotion::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 9;
	name = "Kupfer";

	imageActive = load_image("Hand/Kupfer.png");
	image = load_image("Inventar/Erze/Kupfer.png");
}

