#include "FieldFront.h"
#include "main.h"


FieldFront::FieldFront(void)
{
}


FieldFront::~FieldFront(void)
{
}

void FieldFront::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength)
{
	Field::init(x, y, metricsLength);

	colidingLayer = 3;
}

void FieldFront::removeFromMap(const int32_t &x, const int32_t &y) const
{
	int64_t xy64 = world.int64FromXY(x, y);

	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair =  world.mapFront.equal_range(xy64);

	for (unordered_multimap<int64_t, FieldFront*>::iterator frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
	{
		if (frontIt->second == this) {
			frontIt->second = NULL;
			return;
		}
	}
}

void FieldFront::insertIntoMap(const int32_t &x, const int32_t &y) const
{
	world.mapFront.insert(
		make_pair(
			world.int64FromXY(x, y),
			(FieldFront*) this
		)
	);
}