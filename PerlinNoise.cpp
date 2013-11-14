#include "PerlinNoise.h"
#include "main.h"

double PerlinNoise::findnoise(const double x, const double y, const int z)
{
	int n=((int)x+(int)y*57) ^ (MY_RAND_SEED+z*115);
	n=(n<<13)^n;
	int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	return 1.0-((double)nn/1073741824.0);
}

double PerlinNoise::interpolate(const double a, const double b, const double x)
{
	double ft=x * 3.1415927;
	double f=(1.0-cos(ft))* 0.5;
	return a*(1.0-f)+b*f;
}

double PerlinNoise::noise(const double x, const double y, const int z)
{
	double floorx=(double)((int)x);
	double floory=(double)((int)y);
	double s,t,u,v;
	s=findnoise(floorx, floory, z); 
	t=findnoise(floorx+1, floory, z);
	u=findnoise(floorx, floory+1, z);
	v=findnoise(floorx+1, floory+1, z);
	double int1=interpolate(s, t, x-floorx);
	double int2=interpolate(u, v, x-floorx);
	return interpolate(int1, int2, y-floory);
}

double PerlinNoise::perlinNoise(const int x, const int y, const int z, const double zoom, const double p)
{
	int octaves = 3;

	double getnoise = 0;
	for(int a=0;a<octaves;a++)
	{
		double frequency = pow(2,a);
		double amplitude = pow(p,a);
		getnoise += noise(((double)x)*frequency/zoom,((double)y)/zoom*frequency, z)*amplitude;
	}

	return (getnoise+1)/2;
}

SDL_Surface* PerlinNoise::Render_Clouds(const int x, const int y, const int z, const int w, const int h, const double zoom, const double p)
{
	const SDL_PixelFormat& fmt = *(screen->format);
	SDL_Surface* ret = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, fmt.BitsPerPixel, fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask);
	for(int yi = 0; yi<h; yi++)
	{
		for(int xi = 0; xi<w; xi++)
		{
			int color= (int)(perlinNoise(x+xi, y+yi, z, zoom, p)*255);
			if(color>255)
				color=255;
			if(color<0)
				color=0;

			Uint32 pixel = SDL_MapRGB(ret->format, color, color, color);
			put_pixel32(ret,xi,yi,pixel);
		}
	}
	return ret;
}