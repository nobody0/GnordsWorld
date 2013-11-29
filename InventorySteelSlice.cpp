#include "main.h"
#include "InventorySteelSlice.h"



InventorySteelSlice::InventorySteelSlice(void)
{
	init();
	amount = 1;
}

InventorySteelSlice::InventorySteelSlice(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySteelSlice::~InventorySteelSlice(void)
{
}

void InventorySteelSlice::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
}

void InventorySteelSlice::init()
{
	toolType = Default;
	toolLevel = 3;

	maxAmount = 1;
	name = "Stahlsichel";

	imageActive = load_image("Inventar//Werkzeug/Stahlsichel.png");
	image = load_image("GUI/Werkzeug/Stahlsichel.png");
}