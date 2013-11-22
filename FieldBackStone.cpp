#include "FieldBackStone.h"
#include "main.h"
#include "InventoryStone.h"


FieldBackStone::FieldBackStone(void)
{
}

FieldBackStone::~FieldBackStone(void)
{
}

void FieldBackStone::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Steine/Steine01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Steine/Steine02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Steine/Steine03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Steine/Steine04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Steine/Steine05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Steine/Steine06.png");
		break;
	}
}

void FieldBackStone::myUpdate()
{

}

void FieldBackStone::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
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
		InventoryObject* inventoryObject = new InventoryStone(1);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}