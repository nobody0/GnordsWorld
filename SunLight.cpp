#include "SunLight.h"
#include "main.h"


SunLight::SunLight(void)
{
}


SunLight::~SunLight(void)
{
}

void SunLight::init()
{
	SDL_Surface* dayTime = load_image("Paralax/Tageszeiten.png");
	dayTimePixelCount = dayTime->h * dayTime->w;

	range = 100;
	
	dayTimeColorMap = new Uint32[range * dayTimePixelCount];
	pixelLock = new int[pixelCount];

	Uint32* dayTimePixels = (Uint32*)dayTime->pixels;
	Uint8* dayTimeColorMapIt = (Uint8*)dayTimeColorMap;
	Uint8* colorIt = (Uint8*)&dayTimePixels;

	for (int colorI = 0; colorI<dayTimePixelCount; colorI++)
	{
		for (int i=0; i<range; i++)
		{
			colorIt = (Uint8*)&dayTimePixels[colorI];
			for (int j=0; j<4; j++)
			{
				(*dayTimeColorMapIt) = ((*colorIt)*range - (*colorIt)*i)/range;
				dayTimeColorMapIt++;
				colorIt++;
			}
		}
	}

	updatePrecision();
}

void SunLight::updatePrecision()
{
	precisionShift = lightPrecision;
	precisionAdd = 1<<precisionShift;
	precisionScreenWidth = SCREEN_WIDTH<<precisionShift;
}

void SunLight::shine()
{
	if (lightPrecision != precisionShift) {
		updatePrecision();
	}

	int64_t xy64;
	unordered_map<int64_t, FieldBack*>::const_iterator backIt;

	int32_t worldXStart = (int32_t)world.player.x - SCREEN_WIDTH/2;
	int32_t worldXStartGridded = (int32_t)floor(worldXStart / GRID_SIZE) - 1;
	int32_t worldXEndGridded = worldXStartGridded + (int32_t)ceil(SCREEN_WIDTH / GRID_SIZE) + 1;
	
	int32_t worldYStart = (int32_t)world.player.y - SCREEN_HEIGHT/2;
	int32_t worldYStartGridded = (int32_t)floor(worldYStart / GRID_SIZE);
	int32_t worldYEndGridded = worldYStartGridded + (int32_t)ceil(SCREEN_HEIGHT / GRID_SIZE);

	int dayTimeIndex = (int)((double)dayTime/dayTimeMax * dayTimePixelCount);
	colorMap = &dayTimeColorMap[dayTimeIndex * range];

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

	while (!queue.empty())
	{
		sunLightHelper = queue.top();
		queue.pop();
		sunLightHelper->shine();
		delete sunLightHelper;
	}
}

void SunLight::pushIfValid(SunLightHelper* sunLightHelper)
{
	if (sunLightHelper->isValidPosition)
	{
		queue.push(sunLightHelper);
	}
	else
	{
		delete sunLightHelper;
	}
}