#pragma once

#include "SDL.h"
#include "ShineHelper.h"
#include "concurrent_queue.h"
#include "concurrent_priority_queue.h"

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

	int range;
	Uint32* colorMap; //get color by distance
	int* distanceMap; //get floored distance by [y*width+x]
	
	//concurrency::concurrent_queue<ShineHelper*> queue;
	concurrency::concurrent_priority_queue<ShineHelper*, CompareShineHelpers> queue;

	int x;
	int y;

	void init(const int &range, const Uint32 &color);

	void shine(int x, int y);

	void pushIfValid(ShineHelper* shineHelper);
};