#include "Crafting.h"
#include "main.h"
#include "CraftingRecipeTest.h"


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
	
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());
	recipes.push_back(new CraftingRecipeTest());

	craftingListPages = recipes.size() / craftingListEntriesPerPage;
}


Crafting::~Crafting(void)
{
	
}

void Crafting::setScreenSize()
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