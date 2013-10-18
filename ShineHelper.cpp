#include "ShineHelper.h"
#include "SDL.h"
#include "main.h"
#include "Light.h"

ShineHelper::ShineHelper(Light* light, int lightX, int lightY, int wallness, Uint32* lightMapIt, Uint32* lightPixelsIt) : light(light), lightX(lightX), lightY(lightY), wallness(wallness), lightMapIt(lightMapIt), lightPixelsIt(lightPixelsIt)
{
	isValidPosition = false;

	screenX = light->x + lightX;
	if (screenX < 0 || screenX >= SCREEN_WIDTH)
	{
		return;
	}

	screenY = light->y + lightY;
	if (screenY < 0 || screenY >= SCREEN_HEIGHT)
	{
		return;
	}

	absX = abs(lightX);
	if (absX >= light->range)
	{
		return;
	}

	absY = abs(lightY);
	if (absY >= light->range)
	{
		return;
	}

	distance = light->distanceMap[absY * light->range + absX] + wallness;
	if (distance >= light->range)
	{
		return;
	}

	isValidPosition = true;
}

ShineHelper::~ShineHelper(void)
{

}

bool ShineHelper::operator<(const ShineHelper &that) const
{
	return this->distance > that.distance;
}
bool ShineHelper::operator>(const ShineHelper &that) const
{
	return this->distance < that.distance;
}

void ShineHelper::shine()
{
	Uint32 color = light->colorMap[distance];
	if ((*lightMapIt) >= color)
	{
		return;
	}

	if ((*lightPixelsIt))
	{
		wallness += 2;
	}
	
	(*lightMapIt) = color;

	light->pushIfValid(new ShineHelper(light, lightX+1, lightY, wallness, lightMapIt+1, lightPixelsIt+1));
	light->pushIfValid(new ShineHelper(light, lightX, lightY+1, wallness, lightMapIt+SCREEN_WIDTH, lightPixelsIt+SCREEN_WIDTH));
	light->pushIfValid(new ShineHelper(light, lightX-1, lightY, wallness, lightMapIt-1, lightPixelsIt-1));
	light->pushIfValid(new ShineHelper(light, lightX, lightY-1, wallness, lightMapIt-SCREEN_WIDTH, lightPixelsIt-SCREEN_WIDTH));
}