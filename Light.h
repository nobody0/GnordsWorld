#pragma once

#include "SDL.h"
#include "LightHelper.h"
#include <queue>

struct CompareLightHelpers : public std::binary_function<LightHelper*, LightHelper*, bool>                                                                                     
{
  bool operator()(const LightHelper* lhs, const LightHelper* rhs) const
  {
	  return lhs->distance > rhs->distance;
  }
};

class Light
{
public:
	Light(void);
	virtual ~Light(void);
	
	int precisionShift;
	int precisionAdd;
	int precisionScreenWidth;
	
	int range;
	int rangePP;

	Uint32* colorMap; //get color by distance
	int* distanceMap; //get floored distance by [y*width+x]
	int* pixelLock; //which pixel do already have a job queued
	
	std::priority_queue<LightHelper*, std::vector<LightHelper*>, CompareLightHelpers> queue;

	int x;
	int y;

	void init(const int &range, const Uint32 &color);

	void shine(int x, int y);

	void pushIfValid(LightHelper* LightHelper);
};