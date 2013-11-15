#include "LightHelper.h"
#include "SDL.h"
#include "main.h"
#include "Light.h"

LightHelper::LightHelper(Light* light, int screenX, int screenY, int wallness,int* distanceOffsetIt,  int* pixelLockIt, Uint32* lightMapIt, Uint32* lightPixelsIt) : light(light), screenX(screenX), screenY(screenY), wallness(wallness), distanceOffsetIt(distanceOffsetIt), pixelLockIt(pixelLockIt), lightMapIt(lightMapIt), lightPixelsIt(lightPixelsIt)
{
	isValidPosition = false;

	//calculate xStart and xEnd
	if (screenX < 0)
	{
		if (screenX+light->precisionAdd <= 0)
		{
			return;
		}

		xStart = 0;

		//adjust the pointers
		_distanceOffsetIt = distanceOffsetIt - screenX;
		_pixelLockIt = pixelLockIt - screenX;
		_lightMapIt = lightMapIt - screenX;
		_lightPixelsIt = lightPixelsIt - screenX;
	}
	else
	{
		xStart = screenX;

		_distanceOffsetIt = distanceOffsetIt;
		_pixelLockIt = pixelLockIt;
		_lightMapIt = lightMapIt;
		_lightPixelsIt = lightPixelsIt;
	}
	xEnd = screenX+light->precisionAdd;
	if (xEnd >= SCREEN_WIDTH)
	{
		xEnd = SCREEN_WIDTH;
	}
	xRange = xEnd - xStart;
	if (xRange <= 0)
	{
		return;
	}

	//calculate yStart and yEnd
	if (screenY < 0)
	{
		if (screenY+light->precisionAdd <= 0)
		{
			return;
		}

		yStart = 0;

		//adjust the pointers
		int correction = screenY*SCREEN_WIDTH;
		_distanceOffsetIt = _distanceOffsetIt - screenY*light->rangePP;
		_pixelLockIt = _pixelLockIt - correction;
		_lightMapIt = _lightMapIt - correction;
		_lightPixelsIt = _lightPixelsIt - correction;
	}
	else
	{
		yStart = screenY;
	}
	yEnd = screenY+light->precisionAdd;
	if (yEnd >= SCREEN_HEIGHT)
	{
		yEnd = SCREEN_HEIGHT;
	}
	yRange = yEnd - yStart;
	if (yRange <= 0)
	{
		return;
	}

	//check if someone else has been on this pixel before
	if ((*_pixelLockIt) <= wallness)
	{
		return;
	}
	else
	{
		(*_pixelLockIt) = wallness;
	}

	//calcualte wallness
	int wallnessAdd = 0;
	for (int x=xStart; x<xEnd; x++)
	{
		for (int y=yStart; y<yEnd; y++)
		{
			if ((*_lightPixelsIt))
			{
				wallnessAdd += 2;
			}
			_lightPixelsIt += SCREEN_WIDTH;
		}
		_lightPixelsIt -= SCREEN_WIDTH*yRange;
		_lightPixelsIt++;
	}
	this->wallness += wallnessAdd / min(xRange, yRange);

	//calculate distance
	distance = (*_distanceOffsetIt) + this->wallness;
	if (distance >= light->range)
	{
		return;
	}

	isValidPosition = true;
}

LightHelper::~LightHelper(void)
{

}

void LightHelper::shine()
{
	bool coloredAtleastOnePixel = false;

	Uint32 color;

	for (int x=xStart; x<xEnd; x++)
	{
		for (int y=yStart; y<yEnd; y++)
		{
			distance = (*_distanceOffsetIt) + this->wallness;
			if (distance < light->range)
			{
				color = light->colorMap[distance];
				if ((*_lightMapIt) < color)
				{
					(*_lightMapIt) = color;
					coloredAtleastOnePixel = true;
				}
			}

			_distanceOffsetIt += light->rangePP;

			_lightMapIt += SCREEN_WIDTH;
		}
		_distanceOffsetIt -= light->rangePP*yRange;
		_distanceOffsetIt++;

		_lightMapIt -= SCREEN_WIDTH*yRange;
		_lightMapIt++;
	}

	if (!coloredAtleastOnePixel)
	{
		return;
	}


	if (screenX > light->x)
	{
		light->pushIfValid(new LightHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt+light->precisionAdd, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new LightHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt-light->precisionAdd, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}
	else if (screenX < light->x)
	{
		light->pushIfValid(new LightHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt-light->precisionAdd, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new LightHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt+light->precisionAdd, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}
	else
	{
		light->pushIfValid(new LightHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt+light->precisionAdd, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new LightHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt+light->precisionAdd, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}

	if (screenY > light->y)
	{
		light->pushIfValid(new LightHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt+(light->rangePP<<light->precisionShift), pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new LightHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt-(light->rangePP<<light->precisionShift), pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
	else if (screenY < light->y)
	{
		light->pushIfValid(new LightHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt-(light->rangePP<<light->precisionShift), pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new LightHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt+(light->rangePP<<light->precisionShift), pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
	else
	{
		light->pushIfValid(new LightHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt+(light->rangePP<<light->precisionShift), pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new LightHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt+(light->rangePP<<light->precisionShift), pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
}