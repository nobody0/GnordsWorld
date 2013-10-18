#pragma once

#include "SDL.h"

class Light;

class ShineHelper
{
public:
	Light* light;

	int wallness;
	int* pixelLockIt;
	Uint32* lightMapIt;
	Uint32* lightPixelsIt;

	int screenX;
	int screenY;
	int* distanceOffsetIt;
	int distance; //euclid distance + wallness

	bool isValidPosition;

	ShineHelper(Light* light, int screenX, int screenY, int wallness, int* distanceOffsetIt, int* pixelLockIt, Uint32* lightMapIt, Uint32* lightPixelsIt);
	~ShineHelper(void);

	void shine();
};
