#include "FieldBackEarth.h"
#include "main.h"
#include "FieldBackGrass.h"
#include "InventoryEarth.h"


FieldBackEarth::FieldBackEarth(void)
{
}


FieldBackEarth::~FieldBackEarth(void)
{
}

void FieldBackEarth::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	switch (myRand(x ^ (y<<2)) % 6)
	{
	case 0:
		image = load_image("Background/Erze/Erde/Erde01.png");
		break;
	case 1:
		image = load_image("Background/Erze/Erde/Erde02.png");
		break;
	case 2:
		image = load_image("Background/Erze/Erde/Erde03.png");
		break;
	case 3:
		image = load_image("Background/Erze/Erde/Erde04.png");
		break;
	case 4:
		image = load_image("Background/Erze/Erde/Erde05.png");
		break;
	case 5:
		image = load_image("Background/Erze/Erde/Erde06.png");
		break;
	}
}

void FieldBackEarth::myUpdate()
{
	if (updateCounter > 10) {
		unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(xGridded, yGridded-1));
		if (backIt != world.mapBack.end())
		{
			if (backIt->second == NULL)
			{
				removeFromMap();

				FieldBackGrass* fieldBackGrass = new FieldBackGrass();
				fieldBackGrass->init(xGridded*GRID_SIZE, yGridded*GRID_SIZE);

				//reminder: this has to be the very last thing to execute!
				delete this;
				return;
			}
		}

		updateCounter = 0;
	} else {
		updateCounter++;
	}
}

void FieldBackEarth::onUsed()
{
	InventoryObject* inventoryObject = new InventoryEarth(1);
	world.player.inventory.add(inventoryObject);
	FieldBack::onUsed();
}