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

	colorMap = new Uint32[range];
	distanceMap = new int[range*range];

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

	for (int x = range - 1; x >= 0 ; x--)
	{
		for (int y = range - 1; y >= 0 ; y--)
		{
			distanceMap[y * range + x] = (int)sqrt(x*x + y*y);
		}
	}
}

void Light::shine(int x, int y)
{
	this->x = x;
	this->y = y;

	int offset = y*SCREEN_WIDTH + x;
	
	queue.push(ShineHelper(this, 0, 0, 0, lightMap + offset, ((Uint32*)lightScreen->pixels) + offset));

	while (!queue.empty())
	{
		queue.top().shine();
		queue.pop();
	}
}