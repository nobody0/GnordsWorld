#include "Light.h"
#include "main.h"
#include "ShineHelper.h"


Light::Light(void)
{
	colorMap = NULL;
	distanceMap = NULL;
}


Light::~Light(void)
{
}

void Light::init(const int &range, const Uint32 &color)
{
	this->range = range;
	rangePP = range + 1;

	colorMap = new Uint32[range];
	distanceMap = new int[rangePP*rangePP+rangePP];
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

	for (int x = rangePP - 1; x >= 0 ; x--)
	{
		for (int y = rangePP - 1; y >= 0 ; y--)
		{
			distanceMap[y * rangePP + x] = (int)sqrt(x*x + y*y);
		}
	}

	//overflow area
	for (int z = rangePP - 1; z >= 0 ; z--)
	{
		distanceMap[rangePP*rangePP+z] = range+1;
	}
}

void Light::shine(int x, int y)
{
	this->x = x;
	this->y = y;

	int offset = y*SCREEN_WIDTH + x;

	for (int i = pixelCount - 1; i >= 0 ; i--)
	{
		pixelLock[i] = range;
	}

	pushIfValid(new ShineHelper(this, x, y, 0, distanceMap, pixelLock+offset, lightMap+offset, ((Uint32*)lightScreen->pixels)+offset));
	
	ShineHelper* shineHelper;

	while (!queue.empty())
	{
		shineHelper = queue.top();
		queue.pop();
		shineHelper->shine();
		delete shineHelper;
	}
}

void Light::pushIfValid(ShineHelper* shineHelper)
{
	if (shineHelper->isValidPosition)
	{
		queue.push(shineHelper);
	}
	else
	{
		delete shineHelper;
	}
}