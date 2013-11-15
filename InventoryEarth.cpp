#include "main.h"
#include "InventoryEarth.h"
#include "FieldBackEarth.h"


InventoryEarth::InventoryEarth(void)
{
	amount = 1;
}

InventoryEarth::InventoryEarth(int32_t amount)
{
	this->amount = amount;
	imageActive = load_image("Background/Erze/Erde/Erde01.png");
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
	}
}