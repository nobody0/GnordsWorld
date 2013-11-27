#include "FieldBackWater.h"
#include "InventoryWater.h"
#include "main.h"


FieldBackWater::FieldBackWater(void)
{
}


FieldBackWater::~FieldBackWater(void)
{
}

void FieldBackWater::init(const int32_t &x, const int32_t &y)
{
	FieldBack::init(x, y);

	setWaterLevel(maxWaterLevel);
}

void FieldBackWater::myUpdate()
{
	if (updateCounter > 0.5) {
		unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(xGridded, yGridded-1));
		if (backIt != world.mapBack.end())
		{
			if (backIt->second == NULL)
			{
				//removeFromMap();

				//FieldBackGrass* fieldBackGrass = new FieldBackGrass();
				//fieldBackGrass->init(xGridded*GRID_SIZE, yGridded*GRID_SIZE);
				//fieldBackGrass->health = health;

				//delete this;
				//return;
			}
		}

		updateCounter = 0;
	} else {
		updateCounter += deltaTime;
	}
}

void FieldBackWater::onUsed(const ToolTypes &toolType, const int32_t &toolLevel)
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
		InventoryObject* inventoryObject = new InventoryWater(waterLevel);
		world.player.inventory.add(inventoryObject);

		removeFromMap();

		delete this;
		return;
	}
}

void FieldBackWater::setWaterLevel(int newWaterLevel)
{
	waterLevel = newWaterLevel;

	image = load_image("Background/Wasser/Wasser_"+to_string(waterLevel)+".png");
}