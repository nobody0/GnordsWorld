#include "FieldBackCopper.h"
#include "main.h"
#include "InventoryCopper.h"


FieldBackCopper::FieldBackCopper(void)
{
}

FieldBackCopper::~FieldBackCopper(void)
{
}

void FieldBackCopper::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Kupfer/Kupfer01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Kupfer/Kupfer02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Kupfer/Kupfer03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Kupfer/Kupfer04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Kupfer/Kupfer05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Kupfer/Kupfer06.png");
		break;
	}
}

void FieldBackCopper::myUpdate()
{
	if (updateCounter > 2) {
		unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(xGridded, yGridded-1));

		if (backIt != world.mapBack.end())
		{
			if (backIt->second == NULL)
			{
				removeFromMap();
				delete this;
				return;
			}
		}
		updateCounter = 0;
	} 
	else 
	{
		updateCounter += deltaTime;
	}
}

void FieldBackCopper::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
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
		InventoryObject* inventoryObject = new InventoryCopper(1);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}