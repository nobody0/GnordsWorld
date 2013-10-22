#pragma once

#include "SDL.h"

class Light;

class LightHelper
{
public:
	Light* light;

	//stuff which is passed down to the siblings
	int wallness;
	int* pixelLockIt;
	Uint32* lightMapIt;
	Uint32* lightPixelsIt;
	int screenX;
	int screenY;
	int* distanceOffsetIt;


	//caluclated stuff for this node only
	int distance; //euclid distance + wallness, used for sorting

	int xStart;
	int xEnd;
	int yStart;
	int yEnd;
	int xRange;
	int yRange;

	int* _distanceOffsetIt;
	int* _pixelLockIt;
	Uint32* _lightMapIt;
	Uint32* _lightPixelsIt;

	bool isValidPosition;


	LightHelper(Light* light, int screenX, int screenY, int wallness, int* distanceOffsetIt, int* pixelLockIt, Uint32* lightMapIt, Uint32* lightPixelsIt);
	~LightHelper(void);

	void shine();
};
