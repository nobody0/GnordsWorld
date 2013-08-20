#pragma once

#include "SDL.h"

class Paralax
{
public:
	Paralax(void);
	virtual ~Paralax(void);

	SDL_Surface* image;

	float x;
	float y;

	float scrollSpeed;

	void draw();

	void update();
};

