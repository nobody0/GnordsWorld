#include "Crafting.h"
#include "main.h"
#include "CraftingRecipeAlchemyTable.h"
#include "CraftingRecipeAnvil.h"
#include "CraftingRecipeCopperAxe.h"
#include "CraftingRecipeCopperIngot.h"
#include "CraftingRecipeCopperPick.h"
#include "CraftingRecipeCopperSlice.h"
#include "CraftingRecipeMetalBucket.h"
#include "CraftingRecipeRope.h"
#include "CraftingRecipeSilverAxe.h"
#include "CraftingRecipeSilverIngot.h"
#include "CraftingRecipeSilverPick.h"
#include "CraftingRecipeSilverSlice.h"
#include "CraftingRecipeSteelAxe.h"
#include "CraftingRecipeSteelIngot.h"
#include "CraftingRecipeSteelPick.h"
#include "CraftingRecipeSteelSlice.h"
#include "CraftingRecipeStick.h"
#include "CraftingRecipeStoneAxe.h"
#include "CraftingRecipeStonePick.h"
#include "CraftingRecipeStoneSlice.h"
#include "CraftingRecipeTorch.h"
#include "CraftingRecipeWoodenPlank.h"
#include "CraftingRecipeWorkBanch.h"


Crafting::Crafting(void)
{
	craftingX = world.player.inventory.backgroundX + 525;
	craftingY = world.player.inventory.backgroundY + 15;

	listOffsetX = 30;
	listOffsetY = 40;

	activeOffsetX = 140;
	activeOffsetY = 10;

	craftingRecipeHeight = 20;
	craftingRecipeWidth = 100;
	
	craftingButtonOffsetX = 20;
	craftingButtonOffsetY = 150;
	craftingButtonHeight = 20;
	craftingButtonWidth = 100;

	activeRecipeIndex = -1;
	craftingListPage = 0;
	craftingListEntriesPerPage = 15;

	pagginationXButtonLeft = 25;
	pagginationXButtonRight = 110;
	pagginationYButton = 350;
	
	recipes.push_back(new CraftingRecipeStick());
	recipes.push_back(new CraftingRecipeWoodenPlank());
	recipes.push_back(new CraftingRecipeCopperIngot());
	recipes.push_back(new CraftingRecipeSteelIngot());
	recipes.push_back(new CraftingRecipeSilverIngot());
	recipes.push_back(new CraftingRecipeStoneAxe());
	recipes.push_back(new CraftingRecipeStonePick());
	recipes.push_back(new CraftingRecipeStoneSlice());
	recipes.push_back(new CraftingRecipeCopperAxe());
	recipes.push_back(new CraftingRecipeCopperPick());
	recipes.push_back(new CraftingRecipeCopperSlice());
	recipes.push_back(new CraftingRecipeSteelAxe());
	recipes.push_back(new CraftingRecipeSteelPick());
	recipes.push_back(new CraftingRecipeSteelSlice());
	recipes.push_back(new CraftingRecipeSilverAxe());
	recipes.push_back(new CraftingRecipeSilverPick());
	recipes.push_back(new CraftingRecipeSilverSlice());
	recipes.push_back(new CraftingRecipeMetalBucket());
	recipes.push_back(new CraftingRecipeWorkBanch());
	recipes.push_back(new CraftingRecipeAnvil());
	recipes.push_back(new CraftingRecipeAlchemyTable());
	recipes.push_back(new CraftingRecipeRope());
	recipes.push_back(new CraftingRecipeTorch());
	
	craftingListPages = recipes.size() / craftingListEntriesPerPage;
}


Crafting::~Crafting(void)
{
	
}



void Crafting::draw()
{
	apply_surface(craftingX, craftingY, load_image("CraftingGUI/G_W_crafting_liste.png"), screen);

	unsigned int pos = 0;
	for (unsigned int i=craftingListPage*craftingListEntriesPerPage; i<recipes.size() && pos<craftingListEntriesPerPage; i++, pos++)
	{
		recipes[i]->draw(craftingX+listOffsetX, craftingY+listOffsetY + pos*craftingRecipeHeight);
	}

	if (activeRecipeIndex != -1)
	{
		recipes[activeRecipeIndex]->drawActive(craftingX+activeOffsetX, craftingY+activeOffsetY);
	}

	if (craftingListPage > 0)
	{
		apply_surface(craftingX+pagginationXButtonLeft, craftingY+pagginationYButton, load_image("CraftingGUI/left.jpg"), screen);
	}

	if (craftingListPage < craftingListPages)
	{
		apply_surface(craftingX+pagginationXButtonRight, craftingY+pagginationYButton, load_image("CraftingGUI/right.jpg"), screen);
	}

	SDL_Color color = {0,0,0};
	apply_font(craftingX+pagginationXButtonLeft+35, craftingY+pagginationYButton, screen, load_font("arial.ttf", 15), to_string(craftingListPage) + "/" + to_string(craftingListPages), color);
}

void Crafting::onMouseDown()
{
	int xRelativeTo = mouseX - craftingX - listOffsetX;
	int yRelativeTo = mouseY - craftingY - listOffsetY;

	if (xRelativeTo < 0 || xRelativeTo > craftingRecipeWidth
		|| yRelativeTo < 0 || yRelativeTo > craftingListEntriesPerPage*craftingRecipeHeight)
	{
		Rect coliderRect;
		coliderRect.x = craftingX+pagginationXButtonLeft;
		coliderRect.y = craftingY+pagginationYButton;
		coliderRect.h = 13;
		coliderRect.w = 13;


		if (craftingListPage > 0 && coliderRect.collidesWith(mouseX, mouseY))
		{
			craftingListPage--;
			return;
		}

		coliderRect.x = craftingX+pagginationXButtonRight;
		if (craftingListPage < craftingListPages && coliderRect.collidesWith(mouseX, mouseY))
		{
			craftingListPage++;
			return;
		}

		xRelativeTo = mouseX - craftingX - activeOffsetX - craftingButtonOffsetX;
		yRelativeTo = mouseY - craftingY - activeOffsetY - craftingButtonOffsetY;

		if (activeRecipeIndex != -1)
		{
			if (xRelativeTo < 0 || xRelativeTo > craftingButtonWidth
				|| yRelativeTo < 0 || yRelativeTo > craftingButtonHeight)
			{
				return;
			}

			recipes[activeRecipeIndex]->doCraft();
		}

		return;
	}

	activeRecipeIndex = (yRelativeTo/craftingRecipeHeight) + craftingListPage*craftingListEntriesPerPage;
}