#pragma once

#include "SDL.h"

class Rect
{
public:
	Rect(void);
	~Rect(void);
	
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	bool collidesWith(const Rect &rect2);
};

