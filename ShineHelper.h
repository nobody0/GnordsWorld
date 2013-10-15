#pragma once

#include "SDL.h"

class Light;

class ShineHelper
{
public:
	Light* light;

	int lightX;
	int lightY;
	int wallness;
	Uint32* lightMapIt;
	Uint32* lightPixelsIt;

	int screenX;
	int screenY;
	int absX;
	int absY;
	int distance;
	int cost;

	ShineHelper(Light* light, int lightX, int lightY, int wallness, Uint32* lightMapIt, Uint32* lightPixelsIt);
	
	bool operator<(const ShineHelper &that) const;
	bool operator>(const ShineHelper &that) const;

	void shine();
};
