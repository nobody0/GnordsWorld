#include "SunLightHelper.h"
#include "SDL.h"
#include "main.h"
#include "SunLight.h"

SunLightHelper::SunLightHelper(SunLight* sunLight, int screenX, int screenY, int wallness, int* pixelLockIt, Uint32* sunLightMapIt, Uint32* sunLightPixelsIt) : sunLight(sunLight), screenX(screenX), screenY(screenY), wallness(wallness), pixelLockIt(pixelLockIt), sunLightMapIt(sunLightMapIt), sunLightPixelsIt(sunLightPixelsIt)
{
	isValidPosition = false;

	//calculate xStart and xEnd
	if (screenX < 0)
	{
		if (screenX+sunLight->precisionAdd <= 0)
		{
			return;
		}

		xStart = 0;

		//adjust the pointers
		_pixelLockIt = pixelLockIt - screenX;
		_sunLightMapIt = sunLightMapIt - screenX;
		_sunLightPixelsIt = sunLightPixelsIt - screenX;
	}
	else
	{
		xStart = screenX;

		_pixelLockIt = pixelLockIt;
		_sunLightMapIt = sunLightMapIt;
		_sunLightPixelsIt = sunLightPixelsIt;
	}
	xEnd = screenX+sunLight->precisionAdd;
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
		if (screenY+sunLight->precisionAdd <= 0)
		{
			return;
		}

		yStart = 0;

		//adjust the pointers
		int correction = screenY*SCREEN_WIDTH;
		_pixelLockIt = _pixelLockIt - correction;
		_sunLightMapIt = _sunLightMapIt - correction;
		_sunLightPixelsIt = _sunLightPixelsIt - correction;
	}
	else
	{
		yStart = screenY;
	}
	yEnd = screenY+sunLight->precisionAdd;
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
			if ((*_sunLightPixelsIt))
			{
				wallnessAdd += 2;
			}
			_sunLightPixelsIt += SCREEN_WIDTH;
		}
		_sunLightPixelsIt -= SCREEN_WIDTH*yRange;
		_sunLightPixelsIt++;
	}
	this->wallness += wallnessAdd / ((xRange + yRange) / 2);

	if (this->wallness >= sunLight->range)
	{
		return;
	}

	isValidPosition = true;
}

SunLightHelper::~SunLightHelper(void)
{

}

void SunLightHelper::shine()
{
	bool coloredAtleastOnePixel = false;

	Uint32 color = sunLight->colorMap[wallness];;
	if (wallness < sunLight->range)
	{
		for (int x=xStart; x<xEnd; x++)
		{
			for (int y=yStart; y<yEnd; y++)
			{
				if ((*_sunLightMapIt) < color)
				{
					(*_sunLightMapIt) = color;
					coloredAtleastOnePixel = true;
				}

				_sunLightMapIt += SCREEN_WIDTH;
			}

			_sunLightMapIt -= SCREEN_WIDTH*yRange;
			_sunLightMapIt++;
		}
	}

	if (!coloredAtleastOnePixel)
	{
		return;
	}

	sunLight->pushIfValid(new SunLightHelper(sunLight, screenX+sunLight->precisionAdd, screenY, wallness, pixelLockIt+sunLight->precisionAdd, sunLightMapIt+sunLight->precisionAdd, sunLightPixelsIt+sunLight->precisionAdd));
	sunLight->pushIfValid(new SunLightHelper(sunLight, screenX-sunLight->precisionAdd, screenY, wallness, pixelLockIt-sunLight->precisionAdd, sunLightMapIt-sunLight->precisionAdd, sunLightPixelsIt-sunLight->precisionAdd));

	sunLight->pushIfValid(new SunLightHelper(sunLight, screenX, screenY+sunLight->precisionAdd, wallness, pixelLockIt+sunLight->precisionScreenWidth, sunLightMapIt+sunLight->precisionScreenWidth, sunLightPixelsIt+sunLight->precisionScreenWidth));
	sunLight->pushIfValid(new SunLightHelper(sunLight, screenX, screenY-sunLight->precisionAdd, wallness, pixelLockIt-sunLight->precisionScreenWidth, sunLightMapIt-sunLight->precisionScreenWidth, sunLightPixelsIt-sunLight->precisionScreenWidth));
}