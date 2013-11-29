#include "FieldBackHemp.h"
#include "main.h"
#include "InventoryHemp.h"


FieldBackHemp::FieldBackHemp(void)
{
}


FieldBackHemp::~FieldBackHemp(void)
{
}

void FieldBackHemp::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	image = load_image("Background/Pflanzen/Pflanze_Hanf.png");
}

void FieldBackHemp::myUpdate()
{

}

void FieldBackHemp::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
{
	if (toolType == appropriateTool)
	{
		health -= 2*toolLevel*deltaTime;
	}
	else
	{
		health -= toolLevel*deltaTime;
	}

	if (health <= 0)
	{
		InventoryObject* inventoryObject = new InventoryHemp(1);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}