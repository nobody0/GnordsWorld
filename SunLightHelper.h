#pragma once

#include "SDL.h"

class SunLight;

class SunLightHelper
{
public:
	SunLight* sunLight;

	//stuff which is passed down to the siblings
	int wallness;
	int* pixelLockIt;
	Uint32* sunLightMapIt;
	Uint32* sunLightPixelsIt;
	int screenX;
	int screenY;


	//caluclated stuff for this node only
	int xStart;
	int xEnd;
	int yStart;
	int yEnd;
	int xRange;
	int yRange;

	int* _pixelLockIt;
	Uint32* _sunLightMapIt;
	Uint32* _sunLightPixelsIt;

	bool isValidPosition;


	SunLightHelper(SunLight* sunLight, const int screenX, const int screenY, int wallness, int* pixelLockIt, Uint32* sunLightMapIt, Uint32* sunLightPixelsIt);
	~SunLightHelper(void);

	void shine();
};
