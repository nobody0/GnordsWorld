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

	if ((*lightPixelsIt))
	{
		this->wallness += 2;
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
	if ((*lightMapIt) >= color)
	{
		return;
	}
	
	(*lightMapIt) = color;

	if (screenX > light->x)
	{
		light->pushIfValid(new ShineHelper(light, screenX+1, screenY, wallness, distanceOffsetIt+1, pixelLockIt+1, lightMapIt+1, lightPixelsIt+1));
		light->pushIfValid(new ShineHelper(light, screenX-1, screenY, wallness, distanceOffsetIt-1, pixelLockIt-1, lightMapIt-1, lightPixelsIt-1));
	}
	else if (screenX < light->x)
	{
		light->pushIfValid(new ShineHelper(light, screenX+1, screenY, wallness, distanceOffsetIt-1, pixelLockIt+1, lightMapIt+1, lightPixelsIt+1));
		light->pushIfValid(new ShineHelper(light, screenX-1, screenY, wallness, distanceOffsetIt+1, pixelLockIt-1, lightMapIt-1, lightPixelsIt-1));
	}
	else
	{
		light->pushIfValid(new ShineHelper(light, screenX+1, screenY, wallness, distanceOffsetIt+1, pixelLockIt+1, lightMapIt+1, lightPixelsIt+1));
		light->pushIfValid(new ShineHelper(light, screenX-1, screenY, wallness, distanceOffsetIt+1, pixelLockIt-1, lightMapIt-1, lightPixelsIt-1));
	}

	if (screenY > light->y)
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+1, wallness, distanceOffsetIt+light->rangePP, pixelLockIt+SCREEN_WIDTH, lightMapIt+SCREEN_WIDTH, lightPixelsIt+SCREEN_WIDTH));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-1, wallness, distanceOffsetIt-light->rangePP, pixelLockIt-SCREEN_WIDTH, lightMapIt-SCREEN_WIDTH, lightPixelsIt-SCREEN_WIDTH));
	}
	else if (screenY < light->y)
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+1, wallness, distanceOffsetIt-light->rangePP, pixelLockIt+SCREEN_WIDTH, lightMapIt+SCREEN_WIDTH, lightPixelsIt+SCREEN_WIDTH));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-1, wallness, distanceOffsetIt+light->rangePP, pixelLockIt-SCREEN_WIDTH, lightMapIt-SCREEN_WIDTH, lightPixelsIt-SCREEN_WIDTH));
	}
	else
	{
		light->pushIfValid(new ShineHelper(light, screenX, screenY+1, wallness, distanceOffsetIt+light->rangePP, pixelLockIt+SCREEN_WIDTH, lightMapIt+SCREEN_WIDTH, lightPixelsIt+SCREEN_WIDTH));
		light->pushIfValid(new ShineHelper(light, screenX, screenY-1, wallness, distanceOffsetIt+light->rangePP, pixelLockIt-SCREEN_WIDTH, lightMapIt-SCREEN_WIDTH, lightPixelsIt-SCREEN_WIDTH));
	}
}