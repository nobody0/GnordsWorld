#pragma once

#include "SDL.h"

class PerlinNoise
{
public:
	static double perlinNoise(const int x, const int y, const double zoom, const double p);

	static SDL_Surface* Render_Clouds(const int x, const int y, const int w, const int h, const double zoom, const double p);

private:
	static double findnoise(double x, double y);

	static double interpolate(double a, double b, double x);

	static double noise(double x,double y);
};

