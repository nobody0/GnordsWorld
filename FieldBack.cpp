#include <unordered_map>
#include <utility>
#include "FieldBack.h"
#include "main.h"


FieldBack::FieldBack(void)
{
}


FieldBack::~FieldBack(void)
{
}

void FieldBack::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength, const int32_t &affectedGridsLength)
{
	Field::init(x, y, metricsLength, affectedGridsLength);

	colidingLayer = 2;
}

void FieldBack::onUsed()
{
	removeFromMap();

	//reminder: this has to be the very last thing to execute!
	delete this;
	return;
}

void FieldBack::removeFromMap() const
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::iterator backIt;

	for (int32_t i = 0; i<affectedGridsLength; i++)
	{
		xy64 = affectedGrids[i];

		backIt = world.mapBack.find(xy64);

		if (backIt != world.mapBack.end())
		{
			backIt->second = NULL;
		}
	}
}

void FieldBack::insertIntoMap() const
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::iterator backIt;

	for (int32_t i = 0; i<affectedGridsLength; i++)
	{
		int64_t xy642 = world.int64FromXY(xGridded, yGridded);
		xy64 = affectedGrids[i];
		backIt = world.mapBack.find(xy64);
		if (backIt != world.mapBack.end())
		{
			//TODO if there already is an obejct at that position, do we override it?!?
			backIt->second = (FieldBack*) this;
		}
		else
		{
			world.mapBack.insert(
				make_pair(
					xy64,
					(FieldBack*) this
				)
			);
		}
	}
}