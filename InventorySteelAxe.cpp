#include "main.h"
#include "InventorySteelAxe.h"



InventorySteelAxe::InventorySteelAxe(void)
{
	init();
	amount = 1;
}

InventorySteelAxe::InventorySteelAxe(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySteelAxe::~InventorySteelAxe(void)
{
}

void InventorySteelAxe::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
}

void InventorySteelAxe::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 1;
	name = "Stahlaxt";

	imageActive = load_image("Inventar/Werkzeug/Stahlaxt.png");
	image = load_image("Inventar/Werkzeug/Stahlaxt.png");
}