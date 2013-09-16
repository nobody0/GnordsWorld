#include "FieldBackGrass.h"
#include "main.h"
#include "FieldBackEarth.h"
#include "InventoryEarth.h"


FieldBackGrass::FieldBackGrass(void)
{
}


FieldBackGrass::~FieldBackGrass(void)
{
}

void FieldBackGrass::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Grass/Grass01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Grass/Grass02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Grass/Grass03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Grass/Grass04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Grass/Grass05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Grass/Grass06.png");
		break;
	}
}

void FieldBackGrass::myUpdate()
{
	unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(xGridded, yGridded-1));
	if (backIt != world.mapBack.end())
	{
		if (backIt->second != NULL)
		{
			removeFromMap();

			FieldBackEarth* fieldBackEarth = new FieldBackEarth();
			fieldBackEarth->init(xGridded*GRID_SIZE, yGridded*GRID_SIZE);
			fieldBackEarth->health = health;

			delete this;
			return;
		}
	}
}

void FieldBackGrass::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
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
		InventoryObject* inventoryObject = new InventoryEarth(1);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}