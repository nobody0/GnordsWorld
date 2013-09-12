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

void FieldBack::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength)
{
	Field::init(x, y, metricsLength);

	colidingLayer = 2;
}

void FieldBack::onUsed()
{
	removeFromMap(xGridded, yGridded);

	//reminder: this has to be the very last thing to execute!
	delete this;
	return;
}

void FieldBack::removeFromMap(const int32_t &x, const int32_t &y) const
{
	int64_t xy64 = world.int64FromXY(x, y);

	unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(xy64);

	if (backIt != world.mapBack.end())
	{
		backIt->second = NULL;
	}
}

void FieldBack::insertIntoMap(const int32_t &x, const int32_t &y) const
{
	//TODO if there already is an obejct at that position, do we override it?!?
	unordered_map<int64_t, FieldBack*>::iterator backIt = world.mapBack.find(world.int64FromXY(x, y));
	if (backIt != world.mapBack.end())
	{
		backIt->second = (FieldBack*) this;
	}
	else
	{
		world.mapBack.insert(
			make_pair(
				world.int64FromXY(x, y),
				(FieldBack*) this
			)
		);
	}
}