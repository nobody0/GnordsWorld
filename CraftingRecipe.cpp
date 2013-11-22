#include "CraftingRecipe.h"
#include "main.h"


CraftingRecipe::CraftingRecipe(void)
{
}


CraftingRecipe::~CraftingRecipe(void)
{
}

void CraftingRecipe::draw(int x, int y)
{
	SDL_Color color = {0,0,0};
	apply_font(x, y, screen, load_font("arial.ttf", 15), name, color);
}

void CraftingRecipe::drawActive(int x, int y)
{
	apply_surface(x, y, load_image("CraftingGUI/G_W_crafting.png"), screen);

	SDL_Color color = {0,0,0};
	apply_font(x+10, y+20, screen, load_font("arial.ttf", 15), name, color);
}