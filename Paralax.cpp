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
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_08.png"), 2);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_07.png"), 3);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_06.png"), 4);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_05.png"), 5);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_04.png"), 6);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_03.png"), 7);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_02.png"), 8);
	Paralax::draw2(load_image("Paralax/Biome/Wald_Biom/E_01.png"), 9);
}

void Paralax::draw2(SDL_Surface* image, const float &speed)
{
	const int32_t size = 3762;

	int32_t x = (int32_t)(world.player.x/speed - world.player.x + SCREEN_WIDTH/2);
	x -= (int32_t)(x/size) * size;

	apply_surface(
		x,
		(int32_t)(-342 - world.player.y + SCREEN_HEIGHT/2),
		image,
		screen
	);

	apply_surface(
		x-3762,
		(int32_t)(-342 - world.player.y + SCREEN_HEIGHT/2),
		image,
		screen
	);

	apply_surface(
		x+3762,
		(int32_t)(-342 - world.player.y + SCREEN_HEIGHT/2),
		image,
		screen
	);
}