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
	string craftingName = "Herstellen";

	apply_surface(x, y, load_image("CraftingGUI/G_W_crafting.png"), screen);

	SDL_Color color = {0,0,0};
	SDL_Color colorRed = {255,0,0};

	apply_font(x+10, y+20, screen, load_font("arial.ttf", 15), name, color);

	if (canBeCrafted())
	{
		apply_font(x+world.player.inventory.crafting->craftingButtonOffsetX, y+world.player.inventory.crafting->craftingButtonOffsetY, screen, load_font("arial.ttf", 15), craftingName, color);
	}
	else
	{
		apply_font(x+world.player.inventory.crafting->craftingButtonOffsetX, y+world.player.inventory.crafting->craftingButtonOffsetY, screen, load_font("arial.ttf", 15), craftingName, colorRed);
	}
}

bool CraftingRecipe::canBeCrafted()
{
	for (int i = 0; i < requirements.size(); i++)
	{
		if (world.player.inventory.hasObject(requirements[i]->name, requirements[i]->amount) == false)
		{
			return false;
		}
	}
	return true;
}

