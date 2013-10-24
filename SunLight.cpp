#include "SunLight.h"
#include "main.h"


SunLight::SunLight(void)
{
	precisionShift = 4;
	precisionAdd = 1<<precisionShift;
	precisionScreenWidth = SCREEN_WIDTH<<precisionShift;

	colorMap = NULL;
}


SunLight::~SunLight(void)
{
}

void SunLight::init()
{
	SDL_PixelFormat* fmt = screen->format;
	Uint32 color = SDL_MapRGBA(fmt, 255, 255, 255, 0);

	range = 100;
	rangePP = range + precisionAdd;

	colorMap = new Uint32[range];
	pixelLock = new int[pixelCount];

	Uint8* colorMapIt = (Uint8*)colorMap;
	Uint8* colorIt = (Uint8*)&color;

	for (int i=0; i<range; i++)
	{
		colorIt = (Uint8*)&color;
		for (int j=0; j<4; j++)
		{
			(*colorMapIt) = ((*colorIt)*range - (*colorIt)*i)/range;
			colorMapIt++;
			colorIt++;
		}
	}
}

void SunLight::shine()
{
	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;

	SDL_PixelFormat* fmt = screen->format;
	Uint32 color = SDL_MapRGBA(fmt, 255, 255, 255, 0);

	int32_t worldXStart = (int32_t)world.player.x - SCREEN_WIDTH/2;
	int32_t worldXStartGridded = (int32_t)floor(worldXStart / GRID_SIZE) - 1;
	int32_t worldXEndGridded = worldXStartGridded + (int32_t)ceil(SCREEN_WIDTH / GRID_SIZE) + 1;
	
	int32_t worldYStart = (int32_t)world.player.y - SCREEN_HEIGHT/2;
	int32_t worldYStartGridded = (int32_t)floor(worldYStart / GRID_SIZE);
	int32_t worldYEndGridded = worldYStartGridded + (int32_t)ceil(SCREEN_HEIGHT / GRID_SIZE);

	for (int i = pixelCount - 1; i >= 0 ; i--)
	{
		pixelLock[i] = range;
	}

	for(int32_t xGriddedWorld = worldXStartGridded; xGriddedWorld <= worldXEndGridded; xGriddedWorld++)
	{
		int wallness = 0;

		for (int32_t worldYGridded = worldYStartGridded-100; worldYGridded < worldYStartGridded; worldYGridded++)
		{
			//collsion test outside viewport
			xy64 = world.int64FromXY(xGriddedWorld, worldYGridded);
			backIt = world.mapBack.find(xy64);
			if (backIt != world.mapBack.end())
			{
				if (backIt->second != NULL)
				{
					for (int i = 0; i<backIt->second->metricsLength; i++)
					{
						if (backIt->second->metrics[i].collidesWith(xGriddedWorld*GRID_SIZE, worldYGridded*GRID_SIZE))
						{
							wallness += GRID_SIZE;
						}
					}
				}
			}

			if (wallness >= range)
			{
				break;
			}
		}

		//collsion test inside viewport
		xy64 = world.int64FromXY(xGriddedWorld, worldYStartGridded);
		backIt = world.mapBack.find(xy64);
		if (backIt != world.mapBack.end())
		{
			if (backIt->second != NULL)
			{
				for (int i = 0; i<backIt->second->metricsLength; i++)
				{
					if (backIt->second->metrics[i].intersectsWith(xGriddedWorld*GRID_SIZE, worldYStartGridded*GRID_SIZE))
					{
						wallness += precisionAdd - worldYStart%precisionAdd;
					}
				}
			}
		}

		if (wallness < range)
		{
			int yOffset = -((int32_t)world.player.y)%precisionAdd;
			int yOffsetTimesWidth = yOffset*SCREEN_WIDTH;

			//push start nodes
			int xStart = xGriddedWorld*GRID_SIZE-worldXStart;
			int xEnd = xGriddedWorld*GRID_SIZE-worldXStart+GRID_SIZE;
			for (int x = xStart; x < xEnd; x += precisionAdd)
			{
				pushIfValid(new SunLightHelper(this, x, yOffset, wallness, pixelLock+yOffsetTimesWidth+x, lightMap+yOffsetTimesWidth+x, ((Uint32*)lightScreen->pixels)+yOffsetTimesWidth+x));
			}
		}
	}

	SunLightHelper* sunLightHelper;

	Uint32 start = SDL_GetTicks();
	counter1 = 0;
	counter2 = 0;

	while (!queue.empty())
	{
		sunLightHelper = queue.top();
		queue.pop();
		sunLightHelper->shine();
		delete sunLightHelper;
	}

	cout << SDL_GetTicks()-start << " : " << counter1 << " : " << counter2 << endl;
}

void SunLight::pushIfValid(SunLightHelper* sunLightHelper)
{
	if (sunLightHelper->isValidPosition)
	{
		counter1++;
		queue.push(sunLightHelper);
	}
	else
	{
		counter2++;
		delete sunLightHelper;
	}
}