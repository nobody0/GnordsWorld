#include "World.h"
#include "main.h"
#include "Paralax.h"
#include "FieldBackEarth.h"
#include "FieldBackGrass.h"
#include "FieldBackIron.h"
#include "FieldBackCoal.h"
#include "FieldBackCopper.h"
#include "FieldBackSilver.h"
#include "FieldBackStone.h"


World::World(void)
{
	mapFront.reserve(100000);
	mapBack.reserve(100000);
}

World::~World(void)
{

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
	int32_t r = myRand( (x ^ (y << 4)) ^ (y ^ (x << 2)) );

	r = r % 28;

	if (y < 8 || r > 20)
	{
		world.mapBack.insert(
			make_pair(
				world.int64FromXY(x, y),
				(FieldBack*) NULL
			)
		);
	}
	else
	{
		switch (r % 28)
		{
			case 0:
			{
				FieldBackIron* fieldBackIron = new FieldBackIron();
				fieldBackIron->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
			case 1:
			{
				FieldBackCoal* fieldBackCoal = new FieldBackCoal();
				fieldBackCoal->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
			case 2:
			{
				FieldBackCopper* fieldBackCopper = new FieldBackCopper();
				fieldBackCopper->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
			case 3:
			{
				FieldBackSilver* fieldBackSilver = new FieldBackSilver();
				fieldBackSilver->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
			case 4:
			{
				FieldBackStone* fieldBackStone = new FieldBackStone();
				fieldBackStone->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
			default:
			{
				FieldBackEarth* fieldBackEarth = new FieldBackEarth();
				fieldBackEarth->init(x*GRID_SIZE, y*GRID_SIZE);
				break;
			}
		}
	}
}

void World::onClick()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;

	int32_t xStart;
	int32_t yStart;
	int32_t xEnd;
	int32_t yEnd;
	int32_t x;
	int32_t y;

	int32_t i;

	int32_t mouseWorldX = mouseX + (int32_t)world.player.x - SCREEN_WIDTH/2;
	int32_t mouseWorldY = mouseY + (int32_t)world.player.y - SCREEN_HEIGHT/2;

	xStart = mouseWorldX / GRID_SIZE;
	if (mouseWorldX % GRID_SIZE) xStart--;

	yStart = mouseWorldY / GRID_SIZE;
	if (mouseWorldY % GRID_SIZE) yStart--;

	xEnd = mouseWorldX / GRID_SIZE;
	if (mouseWorldX % GRID_SIZE) xEnd++;

	yEnd = mouseWorldY / GRID_SIZE;
	if (mouseWorldY % GRID_SIZE) yEnd++;

	for (x = xStart; x <= xEnd; x++)
	{
		for (y = yStart; y <= yEnd; y++)
		{
			xy64 = world.int64FromXY(x, y);

			frontItPair = world.mapFront.equal_range(xy64);

			for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
			{
				if (frontIt->second != NULL) //TODO prevent double checking the same object!
				{
					for (i = 0; i<frontIt->second->metricsLength; i++)
					{
						if (frontIt->second->metrics[i].intersectsWith(mouseWorldX, mouseWorldY))
						{
							return frontIt->second->onClick();
						}
					}
				}
			}

			backIt = world.mapBack.find(xy64);
			if (backIt != world.mapBack.end())
			{
				if (backIt->second != NULL) //TODO prevent double checking the same object!
				{
					for (i = 0; i<backIt->second->metricsLength; i++)
					{
						if (backIt->second->metrics[i].intersectsWith(mouseWorldX, mouseWorldY))
						{
							return backIt->second->onClick();
						}
					}
				}
			}
		}
	}
}

void World::update()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;
	pair<unordered_multimap<int64_t, FieldFront*>::iterator, unordered_multimap<int64_t, FieldFront*>::iterator> frontItPair;
	unordered_multimap<int64_t, FieldFront*>::iterator frontIt;
	int32_t x;
	int32_t y;

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

	for (x=updateXStart; x<updateXEnd; x++)
	{
		for (y=updateYStart; y<updateYEnd; y++)
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

	Paralax::draw(100);

	for (x=drawXStart; x<drawXEnd; x++)
	{
		for (y=drawYStart; y<drawYEnd; y++)
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