#include "ShineHelper.h"
#include "SDL.h"
#include "main.h"
#include "Light.h"

ShineHelper::ShineHelper(Light* light, int screenX, int screenY, int wallness,int* distanceOffsetIt,  int* pixelLockIt, Uint32* lightMapIt, Uint32* lightPixelsIt) : light(light), screenX(screenX), screenY(screenY), wallness(wallness), distanceOffsetIt(distanceOffsetIt), pixelLockIt(pixelLockIt), lightMapIt(lightMapIt), lightPixelsIt(lightPixelsIt)
{
	isValidPosition = false;

	if (screenX < 0 || screenX >= SCREEN_WIDTH)
	{
		return;
	}

	if (screenY < 0 || screenY >= SCREEN_HEIGHT)
	{
		return;
	}

	if ((*pixelLockIt) <= wallness)
	{
		return;
	}
	else
	{
		(*pixelLockIt) = wallness;
	}
	
	for (int x=0; x<light->precisionAdd; x++)
	{
		for (int y=0; y<light->precisionAdd; y++)
		{
			if (lightPixelsIt[y*SCREEN_WIDTH+x])
			{
				this->wallness += 2;
			}
		}
	}

	distance = (*distanceOffsetIt) + this->wallness;
	if (distance >= light->range)
	{
		return;
	}

	isValidPosition = true;
}

ShineHelper::~ShineHelper(void)
{

}

void ShineHelper::shine()
{
	Uint32 color = light->colorMap[distance];

	bool coloredAtleastOnePixel = false;
	Uint32* lightMapIt2 = lightMapIt;
	for (int x=0; x<light->precisionAdd; x++)
	{
		for (int y=0; y<light->precisionAdd; y++)
		{
			if ((*lightMapIt2) < color)
			{
				(*lightMapIt2) = color;
				coloredAtleastOnePixel = true;
			}
			lightMapIt2 += SCREEN_WIDTH;
		}
		lightMapIt2 -= SCREEN_WIDTH<<light->precisionShift;
		lightMapIt2++;
	}

	if (!coloredAtleastOnePixel)
	{
		return;
	}

	if (screenX > light->x)
	{
		light->pushIfValid(new ShineHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt+1, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new ShineHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt-1, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}
	else if (screenX < light->x)
	{
		light->pushIfValid(new ShineHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt-1, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new ShineHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt+1, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}
	else
	{
		light->pushIfValid(new ShineHelper(light, screenX+light->precisionAdd, screenY, wallness, distanceOffsetIt+1, pixelLockIt+light->precisionAdd, lightMapIt+light->precisionAdd, lightPixelsIt+light->precisionAdd));
		light->pushIfValid(new ShineHelper(light, screenX-light->precisionAdd, screenY, wallness, distanceOffsetIt+1, pixelLockIt-light->precisionAdd, lightMapIt-light->precisionAdd, lightPixelsIt-light->precisionAdd));
	}

	if (screenY > light->y)
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt+light->rangePP, pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt-light->rangePP, pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
	else if (screenY < light->y)
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt-light->rangePP, pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt+light->rangePP, pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
	else
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+light->precisionAdd, wallness, distanceOffsetIt+light->rangePP, pixelLockIt+light->precisionScreenWidth, lightMapIt+light->precisionScreenWidth, lightPixelsIt+light->precisionScreenWidth));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-light->precisionAdd, wallness, distanceOffsetIt+light->rangePP, pixelLockIt-light->precisionScreenWidth, lightMapIt-light->precisionScreenWidth, lightPixelsIt-light->precisionScreenWidth));
	}
}