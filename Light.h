#pragma once

#include "SDL.h"
#include "ShineHelper.h"
#include <queue>

struct CompareShineHelpers : public std::binary_function<ShineHelper*, ShineHelper*, bool>                                                                                     
{
  bool operator()(const ShineHelper* lhs, const ShineHelper* rhs) const
  {
	  return lhs->distance > rhs->distance;
  }
};

class Light
{
public:
	Light(void);
	~Light(void);
	
	int precisionShift;
	int precisionAdd;
	int precisionScreenWidth;
	
	int range;
	int rangePP;

	Uint32* colorMap; //get color by distance
	int* distanceMap; //get floored distance by [y*width+x]
	int* pixelLock; //which pixel do already have a job queued
	
	std::priority_queue<ShineHelper*, std::vector<ShineHelper*>, CompareShineHelpers> queue;

	int x;
	int y;

	void init(const int &range, const Uint32 &color);

	void shine(int x, int y);

	void pushIfValid(ShineHelper* shineHelper);
};