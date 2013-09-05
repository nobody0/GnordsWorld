#pragma once

#include "SDL.h"

class Paralax
{
public:
	Paralax(void);
	~Paralax(void);
	
	static void draw();
	static void draw2(SDL_Surface* image, const float &speed);
};