#pragma once

#include "SDL.h"

class PerlinNoise
{
public:
	static inline double perlinNoise(const int x, const int y, const double zoom, const double p);

	static SDL_Surface* Render_Clouds(const int x, const int y, const int w, const int h, const double zoom, const double p);

private:
	static inline double findnoise(double x, double y);

	static inline double interpolate(double a, double b, double x);

	static double noise(double x,double y);
};

