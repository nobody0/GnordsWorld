#include "main.h"
#include "Paralax.h"

Paralax::Paralax()
{

}

Paralax::~Paralax()
{

}

void Paralax::draw(const float &x)
{
	float diff = x - world.player.x;

	//int32_t r = myRand((int32_t)x);
	SDL_Surface* image = load_image("Paralax/Sonne2IlluAxel.png");

	apply_surface(
		(int32_t)(2*diff + x - world.player.x + SCREEN_WIDTH/2),
		(int32_t)(-300 - world.player.y + SCREEN_HEIGHT/2),
		image,
		screen
	);
}