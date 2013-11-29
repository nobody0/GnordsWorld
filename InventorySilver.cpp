#include "main.h"
#include "InventorySilver.h"
#include "FieldBackSilver.h"


InventorySilver::InventorySilver(void)
{
	init();
	amount = 1;
}

InventorySilver::InventorySilver(int32_t amount)
{
	init();
	this->amount = amount;
}


InventorySilver::~InventorySilver(void)
{
}

void InventorySilver::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed(toolType, toolLevel);
	}
	else
	{
		FieldBackSilver* fieldBackSilver = new FieldBackSilver();
		fieldBackSilver->init(x*GRID_SIZE, y*GRID_SIZE);

		world.player.inventory.remove(this, 1);
	}
}

void InventorySilver::init()
{
	toolType = Default;
	toolLevel = 1;

	maxAmount = 99;
	name = "Silber";

	imageActive = load_image("Hand/Silber.png");
	image = load_image("Inventar/Erze/Silber.png");
}

