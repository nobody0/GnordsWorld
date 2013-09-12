#include "FieldFront.h"
#include "main.h"


FieldFront::FieldFront(void)
{
}


FieldFront::~FieldFront(void)
{
}

void FieldFront::init(const int32_t &x, const int32_t &y, const int32_t &metricsLength, const int32_t &affectedGridsLength)
{
	Field::init(x, y, metricsLength, affectedGridsLength);

	colidingLayer = 3;
}

//TODO possibly remove more references from the map, based on metrics
void FieldFront::removeFromMap() const
{
	int64_t xy64;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	for (int32_t i = 0; i<affectedGridsLength; i++)
	{
		xy64 = affectedGrids[i];

		frontItPair =  world.mapFront.equal_range(xy64);

		for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
		{
			if (frontIt->second == this) {
				frontIt->second = NULL;
				return;
			}
		}
	}
}

//TODO possibly add more references from the map, based on metrics
void FieldFront::insertIntoMap() const
{
	int64_t xy64;

	for (int32_t i = 0; i<affectedGridsLength; i++)
	{
		xy64 = affectedGrids[i];

		world.mapFront.insert(
			make_pair(
				xy64,
				(FieldFront*) this
			)
		);
	}
}