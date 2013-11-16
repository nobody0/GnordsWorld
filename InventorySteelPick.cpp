#include "main.h"
#include "InventorySteelPick.h"



InventorySteelPick::InventorySteelPick(void)
{
	init();
	amount = 1;
}

InventorySteelPick::InventorySteelPick(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySteelPick::~InventorySteelPick(void)
{
}

void InventorySteelPick::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
}

void InventorySteelPick::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Stahlhacke";

	imageActive = load_image("Inventar/Werkzeug/Stahlhacke.png");
	image = load_image("Inventar/Werkzeug/Stahlhacke.png");
}