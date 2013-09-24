#pragma once

#include "SDL.h"
#include "Vector2.h"

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

	bool intersectsWith(const Rect &rect2);

	bool collidesWith(const int32_t &dotX, const int32_t &dotY);

	bool intersectsWith(const int32_t &dotX, const int32_t &dotY);

	bool shortenVectorToNotInteresctWith(const Rect &rect2, Vector2 &moveVector);
};

