#include "Light.h"
#include "main.h"
#include "LightHelper.h"


Light::Light(void)
{
}


Light::~Light(void)
{
}

void Light::init(const int &range, const Uint32 &color)
{
	this->range = range;

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

	updatePrecision();
}

void Light::updatePrecision()
{
	precisionShift = lightPrecision;
	precisionAdd = 1<<precisionShift;
	precisionScreenWidth = SCREEN_WIDTH<<precisionShift;

	rangePP = range + precisionAdd;

	delete[] distanceMap;
	distanceMap = new int[rangePP*rangePP+rangePP+rangePP];

	for (int x = rangePP+rangePP - 1; x >= 0 ; x--)
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
	if (lightPrecision != precisionShift) {
		updatePrecision();
	}

	for (int i = pixelCount - 1; i >= 0 ; i--)
	{
		pixelLock[i] = range;
	}

	x -= ((int32_t)world.player.x)%precisionAdd;
	y -= ((int32_t)world.player.y)%precisionAdd;

	this->x = x;
	this->y = y;

	int offset = y*SCREEN_WIDTH + x;

	pushIfValid(new LightHelper(this, x, y, 0, distanceMap, pixelLock+offset, lightMap+offset, ((Uint32*)lightScreen->pixels)+offset));
	
	LightHelper* LightHelper;

	while (!queue.empty())
	{
		LightHelper = queue.top();
		queue.pop();
		LightHelper->shine();
		delete LightHelper;
	}
}

void Light::pushIfValid(LightHelper* LightHelper)
{
	if (LightHelper->isValidPosition)
	{
		queue.push(LightHelper);
	}
	else
	{
		delete LightHelper;
	}
}