#include "ShineHelper.h"
#include "SDL.h"
#include "main.h"
#include "Light.h"

ShineHelper::ShineHelper(Light* light, int lightX, int lightY, int wallness, Uint32* lightMapIt, Uint32* lightPixelsIt) : light(light), lightX(lightX), lightY(lightY), wallness(wallness), lightMapIt(lightMapIt), lightPixelsIt(lightPixelsIt)
{
	screenX = light->x+lightX;
	screenY = light->y+lightY;
	absX = abs(lightX);
	absY = abs(lightY);
	distance = light->distanceMap[absY * light->range + absX] + wallness;
}

bool ShineHelper::operator<(const ShineHelper &that) const
{
	return this->cost > that.cost;
}
bool ShineHelper::operator>(const ShineHelper &that) const
{
	return this->cost < that.cost;
}

void ShineHelper::shine()
{
	if (screenX < 0
		|| screenX >= SCREEN_WIDTH
		|| screenY < 0
		|| screenY >= SCREEN_HEIGHT
		|| absX >= light->range
		|| absY >= light->range
		|| distance >= light->range)
	{
		return;
	}

	Uint32 color = light->colorMap[distance];

	if ((*lightMapIt) >= color)
	{
		return;
	}

	if ((*lightPixelsIt))
	{
		wallness++;
	}
	
	(*lightMapIt) = color;
	
	light->queue.push(ShineHelper(light, lightX+1, lightY, wallness, lightMapIt+1, lightPixelsIt+1));
	light->queue.push(ShineHelper(light, lightX, lightY+1, wallness, lightMapIt+SCREEN_WIDTH, lightPixelsIt+SCREEN_WIDTH));
	light->queue.push(ShineHelper(light, lightX-1, lightY, wallness, lightMapIt-1, lightPixelsIt-1));
	light->queue.push(ShineHelper(light, lightX, lightY-1, wallness, lightMapIt-SCREEN_WIDTH, lightPixelsIt-SCREEN_WIDTH));
}