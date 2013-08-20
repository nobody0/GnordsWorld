#include "Paralax.h"
#include "globals.h"

Paralax::Paralax(void)
{
}

Paralax::~Paralax(void)
{
}

void Paralax::draw()
{
	apply_surface((int32_t)x, (int32_t)y, image, screen);
}