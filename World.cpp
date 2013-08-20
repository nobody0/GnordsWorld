#include "World.h"
#include "main.h"
#include "FieldBackEarth.h"
#include "FieldBackGrass.h"

World::World(void)
{
}

World::~World(void)
{
	/*
	for (unordered_multimap<int64_t, FieldFront*>::iterator frontIt = mapFront.begin(); frontIt != mapFront.end(); frontIt++)
	{
		delete frontIt->second;
	}

	for (unordered_map<int64_t, FieldBack*>::const_iterator backIt = mapBack.begin(); backIt != mapBack.end(); backIt++)
	{
		delete backIt->second;
	}
	*/
}

int64_t World::int64FromXY(const int32_t &x, const int32_t &y)
{
	return (int64_t)x + (((int64_t)y)<<32);
}

void World::init()
{
	player.init(0, 0);
}

void World::generateBack(const int32_t &x, const int32_t &y)
{
	if (y > 0)
	{
		if (myRand(x ^ (y << 2)) % 3 != 0)
		{
			FieldBackEarth* fieldBackEarth = new FieldBackEarth();
			fieldBackEarth->init(x*GRID_SIZE, y*GRID_SIZE);
			return;
		}
	}

	world.mapBack.insert(
		make_pair(
			world.int64FromXY(x, y),
			(FieldBack*) NULL
		)
	);
}

void World::update()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );

	/////////////////RESERVE SOME BUCKETS BEFOREHAND START/////////////////////
	int offset = VISIBLE_GRIDS_X + VISIBLE_GRIDS_Y + UPDATE_GRID_OUT_VIEW_SIZE;

	int reserve = mapFront.size() + offset;
	mapFront.reserve(reserve - reserve%offset + 3*offset);

	reserve = mapBack.size() + offset;
	mapBack.reserve(reserve - reserve%offset + 3*offset);
	/////////////////RESERVE SOME BUCKETS BEFOREHAND END///////////////////////
	
	int32_t updateXStart = player.xGridded - VISIBLE_GRIDS_X/2 - UPDATE_GRID_OUT_VIEW_SIZE/2;
	int32_t updateXEnd = player.xGridded + VISIBLE_GRIDS_X/2 + UPDATE_GRID_OUT_VIEW_SIZE/2;
	
	int32_t updateYStart = player.yGridded - VISIBLE_GRIDS_Y/2 - UPDATE_GRID_OUT_VIEW_SIZE/2;
	int32_t updateYEnd = player.yGridded + VISIBLE_GRIDS_Y/2 + UPDATE_GRID_OUT_VIEW_SIZE/2;

	for (int32_t x=updateXStart; x<updateXEnd; x++)
	{
		for (int32_t y=updateYStart; y<updateYEnd; y++)
		{
			xy64 = int64FromXY(x, y);

			backIt = mapBack.find(xy64);
			if (backIt != mapBack.end())
			{
				if (backIt->second != NULL)
				{
					backIt->second->update();
				}
			}

			frontItPair = mapFront.equal_range(xy64);

			frontIt=frontItPair.first;
			while (frontIt!=frontItPair.second)
			{
				if (frontIt->second != NULL) {
					frontIt->second->update();
				}

				if (frontIt->second == NULL) {
					frontIt = mapFront.erase(frontIt);
				} else {
					++frontIt;
				}
			}
		}
	}

	//TODO test if we have to increase our world
	
	int32_t drawXStart = player.xGridded - VISIBLE_GRIDS_X/2;
	int32_t drawXEnd = player.xGridded + VISIBLE_GRIDS_X/2;
	
	int32_t drawYStart = player.yGridded - VISIBLE_GRIDS_Y/2;
	int32_t drawYEnd = player.yGridded + VISIBLE_GRIDS_Y/2;

	for (int32_t x=drawXStart; x<drawXEnd; x++)
	{
		for (int32_t y=drawYStart; y<drawYEnd; y++)
		{
			xy64 = int64FromXY(x, y);

			backIt = mapBack.find(xy64);
			if (backIt != mapBack.end())
			{
				if (backIt->second != NULL)
				{
					backIt->second->draw();
				}
			}
			else
			{
				generateBack(x, y);
			}

			frontItPair = mapFront.equal_range(xy64);

			for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
			{
				if (frontIt->second != NULL) {
					frontIt->second->draw();
				}
			}
		}
	}

	player.lastDraw = 0;
	player.draw();
}