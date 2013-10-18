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
	player.init(0, -64);
}

void World::generateBack(const int32_t &x, const int32_t &y)
{
	int32_t r = myRand( (x ^ (y << 4)) ^ (y ^ (x << 2)) );

	r = r % 28;

	if (y < 0 || r > 20 && false)
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

	int32_t x;
	int32_t y;

	int32_t i;

	int32_t mouseWorldX = mouseX + (int32_t)world.player.x - SCREEN_WIDTH/2;
	int32_t mouseWorldY = mouseY + (int32_t)world.player.y - SCREEN_HEIGHT/2;

	x = (int32_t)floor((double)mouseWorldX / GRID_SIZE);
	y = (int32_t)floor((double)mouseWorldY / GRID_SIZE);

	Rect colidingRect;
	colidingRect.x = x * GRID_SIZE + 1;
	colidingRect.y = y * GRID_SIZE + 1;
	colidingRect.h = GRID_SIZE - 2;
	colidingRect.w = GRID_SIZE - 2;

	xy64 = world.int64FromXY(x, y);

	frontItPair = world.mapFront.equal_range(xy64);
	for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
	{
		if (frontIt->second != NULL) //TODO prevent double checking the same object!
		{
			for (i = 0; i<frontIt->second->metricsLength; i++)
			{
				if (frontIt->second->metrics[i].collidesWith(colidingRect))
				{
					return player.useTool(frontIt->second, x, y);
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
				if (backIt->second->metrics[i].collidesWith(mouseWorldX, mouseWorldY))
				{
					return player.useTool(backIt->second, x, y);
				}
			}
		}
	}

	player.useTool(NULL, x, y);
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
	int offset = VISIBLE_GRIDS_X + VISIBLE_GRIDS_Y + UPDATE_GRID_OUT_VIEW_SIZE*2;

	int reserve = mapFront.size() + offset;
	mapFront.reserve(reserve - reserve%offset + 3*offset);

	reserve = mapBack.size() + offset;
	mapBack.reserve(reserve - reserve%offset + 3*offset);
	/////////////////RESERVE SOME BUCKETS BEFOREHAND END///////////////////////
	
	int32_t updateXStart = player.xGridded - VISIBLE_GRIDS_X/2 - UPDATE_GRID_OUT_VIEW_SIZE;
	int32_t updateXEnd = player.xGridded + VISIBLE_GRIDS_X/2 + UPDATE_GRID_OUT_VIEW_SIZE;
	
	int32_t updateYStart = player.yGridded - VISIBLE_GRIDS_Y/2 - UPDATE_GRID_OUT_VIEW_SIZE;
	int32_t updateYEnd = player.yGridded + VISIBLE_GRIDS_Y/2 + UPDATE_GRID_OUT_VIEW_SIZE;

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
			else
			{
				generateBack(x, y);
			}
		}
	}

	for (x=updateXStart; x<updateXEnd; x++)
	{
		for (y=updateYStart; y<updateYEnd; y++)
		{
			xy64 = int64FromXY(x, y);

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

	SDL_FillRect(lightScreen, NULL, 0);
	
	int32_t drawXStart = player.xGridded - VISIBLE_GRIDS_X/2;
	int32_t drawXEnd = player.xGridded + VISIBLE_GRIDS_X/2;
	
	int32_t drawYStart = player.yGridded - VISIBLE_GRIDS_Y/2;
	int32_t drawYEnd = player.yGridded + VISIBLE_GRIDS_Y/2;

	Paralax::draw();

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

			frontItPair = mapFront.equal_range(xy64);

			for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
			{
				if (frontIt->second != NULL) {
					frontIt->second->draw();
				}
			}
		}
	}

	player.draw(true);

	if (doShadeScreen)
	{
		for( int i = pixelCount-1; i >= 0; i--)
		{
			lightMap[i] = 0;
		}

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
						backIt->second->shine();
					}
				}

				frontItPair = mapFront.equal_range(xy64);
				for (frontIt=frontItPair.first; frontIt!=frontItPair.second; ++frontIt)
				{
					if (frontIt->second != NULL) {
						frontIt->second->shine();
					}
				}
			}
		}
	}
}