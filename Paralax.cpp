#include "main.h"
#include "Paralax.h"
#include <cstdio>

Paralax::Paralax()
{

}

Paralax::~Paralax()
{

}

void Paralax::draw()
{
	Paralax::drawBG();

	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_08.png"), 2);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_07.png"), 3);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_06.png"), 4);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_05.png"), 5);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_04.png"), 6);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_03.png"), 7);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_02.png"), 8);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_01.png"), 9);
}

void Paralax::drawBG()
{
	SDL_Surface* himmel = load_image("Paralax/Biome/Wald_Biom/Himmel.png");
	SDL_Surface* erde = load_image("Paralax/Biome/Wald_Biom/Erde.png");

	const int32_t width = 256;
	const int32_t height = 256;

	int32_t xGridded = ((int32_t)world.player.x % width) - width;

	int32_t yGridded = ((int32_t)world.player.y % height) - height;

	int32_t maxHimmel = min((int32_t)(SCREEN_HEIGHT/2 - world.player.y), SCREEN_HEIGHT);

	for (int32_t x = xGridded; x<SCREEN_WIDTH; x+=width)
	{
		for (int32_t y = yGridded; y<maxHimmel; y+=height)
		{
			apply_surface(
				x,
				y,
				himmel,
				screen
			);
		}
	}

	for (int32_t x = xGridded; x<SCREEN_WIDTH; x+=width)
	{
		for (int32_t y = maxHimmel; y<SCREEN_HEIGHT; y+=height)
		{
			apply_surface(
				x,
				y,
				erde,
				screen
			);
		}
	}
}

void Paralax::draw2(SDL_Surface* image, const float &speed)
{
	const int32_t width = 3762;
	const int32_t height = 342;

	int32_t xGridded = ((int32_t)(world.player.x/speed - world.player.x) % width) - width;

	int32_t y = -height - world.player.y + SCREEN_HEIGHT/2;

	for (int32_t x = xGridded; x<SCREEN_WIDTH; x+=width)
	{
		apply_surface(
			x,
			y,
			image,
			screen
		);
	}
}