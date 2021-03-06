#include "FieldBackSilver.h"
#include "main.h"
#include "InventorySilver.h"


FieldBackSilver::FieldBackSilver(void)
{
}

FieldBackSilver::~FieldBackSilver(void)
{
}

void FieldBackSilver::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Silber/Silber01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Silber/Silber02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Silber/Silber03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Silber/Silber04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Silber/Silber05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Silber/Silber06.png");
		break;
	}
}

void FieldBackSilver::myUpdate()
{

}

void FieldBackSilver::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
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
		InventoryObject* inventoryObject = new InventorySilver(1);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}