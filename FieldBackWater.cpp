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

	liquid = true;

	setWaterLevel(maxWaterLevel);

	updateCounter = 0;
}

void FieldBackWater::myUpdate()
{
	if (updateCounter > 0.2) {
		unordered_map<int64_t, FieldBack*>::iterator backItBottom = world.mapBack.find(world.int64FromXY(xGridded, yGridded+1));

		if (backItBottom != world.mapBack.end())
		{
			if (backItBottom->second == NULL)
			{
				FieldBackWater* fieldBackWater = new FieldBackWater();
				fieldBackWater->init(xGridded*GRID_SIZE, (yGridded+1)*GRID_SIZE);

				fieldBackWater->setWaterLevel(waterLevel);
				
				removeFromMap();
				delete this;
				return;
			}
			else
			{
				FieldBackWater* otherWater = dynamic_cast<FieldBackWater*>(backItBottom->second);
				if (otherWater && otherWater->waterLevel < maxWaterLevel)
				{
					int summedWaterLevel = waterLevel + otherWater->waterLevel;
					if (summedWaterLevel <= maxWaterLevel)
					{
						otherWater->setWaterLevel(summedWaterLevel);
				
						removeFromMap();
						delete this;
						return;
					}
					else
					{
						otherWater->setWaterLevel(maxWaterLevel);

						setWaterLevel(summedWaterLevel-maxWaterLevel);
					}
				}
			}
		}
		
		FieldBackWater* otherWaterLeft = NULL;
		FieldBackWater* otherWaterRight = NULL;

		if (waterLevel > 1)
		{
			unordered_map<int64_t, FieldBack*>::iterator backItLeft = world.mapBack.find(world.int64FromXY(xGridded-1, yGridded));

			if (backItLeft != world.mapBack.end())
			{
				if (backItLeft->second == NULL)
				{
					FieldBackWater* fieldBackWater = new FieldBackWater();
					fieldBackWater->init((xGridded-1)*GRID_SIZE, yGridded*GRID_SIZE);

					fieldBackWater->waterLevel = 0;

					otherWaterLeft = fieldBackWater;
				}
				else
				{
					FieldBackWater* otherWater = dynamic_cast<FieldBackWater*>(backItLeft->second);
					if (otherWater && otherWater->waterLevel < maxWaterLevel)
					{
						otherWaterLeft = otherWater;
					}
				}
			}
		}

		if ((waterLevel > 1 && otherWaterLeft == NULL) || waterLevel > 2)
		{
			unordered_map<int64_t, FieldBack*>::iterator backItRight = world.mapBack.find(world.int64FromXY(xGridded+1, yGridded));

			if (backItRight != world.mapBack.end())
			{
				if (backItRight->second == NULL)
				{
					FieldBackWater* fieldBackWater = new FieldBackWater();
					fieldBackWater->init((xGridded+1)*GRID_SIZE, yGridded*GRID_SIZE);

					fieldBackWater->waterLevel = 0;

					otherWaterRight = fieldBackWater;
				}
				else
				{
					FieldBackWater* otherWater = dynamic_cast<FieldBackWater*>(backItRight->second);
					if (otherWater && otherWater->waterLevel < maxWaterLevel)
					{
						otherWaterRight = otherWater;
					}
				}
			}
		}

		int otherWaterCounter = 0;
		if (otherWaterLeft != NULL)
		{
			otherWaterCounter++;
		}
		if (otherWaterRight != NULL)
		{
			otherWaterCounter++;
		}

		if (otherWaterCounter > 0)
		{
			int totalWaterLevel = waterLevel;

			if (otherWaterLeft != NULL)
			{
				totalWaterLevel += otherWaterLeft->waterLevel;
			}
			if (otherWaterRight != NULL)
			{
				totalWaterLevel += otherWaterRight->waterLevel;
			}

			int otherShare = totalWaterLevel / (otherWaterCounter+1);
			int myShare = totalWaterLevel - (otherShare*otherWaterCounter);

			if (otherWaterLeft != NULL)
			{
				otherWaterLeft->setWaterLevel(otherShare);
			}
			if (otherWaterRight != NULL)
			{
				otherWaterRight->setWaterLevel(otherShare);
			}

			setWaterLevel(myShare);
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
	int metricsOffset = GRID_SIZE/maxWaterLevel * (maxWaterLevel-newWaterLevel);
	metrics[0].y = y + metricsOffset;
	metrics[0].h = GRID_SIZE - metricsOffset;

	waterLevel = newWaterLevel;

	image = load_image("Background/Wasser/Wasser_"+to_string(waterLevel)+".png");
}