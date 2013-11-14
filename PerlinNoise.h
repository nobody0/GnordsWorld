#pragma once

#include "SDL.h"

class PerlinNoise
{
public:
	static double perlinNoise(const int x, const int y, const int z, const double zoom, const double p);

	static SDL_Surface* Render_Clouds(const int x, const int y, const int z, const int w, const int h, const double zoom, const double p);

private:
	static double findnoise(const double x, const double y, const int z);

	static double interpolate(const double a, const double b, const double x);

	static double noise(const double x, const double y, const int z);
};

