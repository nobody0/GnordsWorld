#pragma once

#include "SDL.h"
#include "SunLightHelper.h"
#include <queue>

struct CompareSunLightHelpers : public std::binary_function<SunLightHelper*, SunLightHelper*, bool>                                                                                     
{
  bool operator()(const SunLightHelper* lhs, const SunLightHelper* rhs) const
  {
	  return lhs->wallness > rhs->wallness;
  }
};

class SunLight
{
public:
	SunLight(void);
	virtual ~SunLight(void);
	
	int precisionShift;
	int precisionAdd;
	int precisionScreenWidth;
	
	int range;

	int dayTimePixelCount;
	
	Uint32* dayTimeColorMap; //get color by distance
	Uint32* colorMap; //get color by distance
	int* pixelLock; //which pixel do already have a job queued
	
	unsigned int pixelCount_old;
	int32_t SCREEN_WIDTH_old;
	
	std::priority_queue<SunLightHelper*, std::vector<SunLightHelper*>, CompareSunLightHelpers> queue;

	int x;
	int y;
	
	void init();

	void setScreenSize();

	void updatePrecision();

	void shine();

	void pushIfValid(SunLightHelper* sunLightHelper);
};

