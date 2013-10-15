#pragma once

#include "SDL.h"
#include "ShineHelper.h"
#include <queue>
#include <stack>

class Light
{
public:
	Light(void);
	~Light(void);

	int range;
	Uint32* colorMap; //get color by distance
	int* distanceMap; //get floored distance by [y*width+x]

	std::stack<ShineHelper> queue;
	//std::priority_queue<ShineHelper> queue;

	int x;
	int y;

	void init(const int &range, const Uint32 &color);

	void shine(int x, int y);
};