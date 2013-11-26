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
	craftingListEntriesPerPage = 16;
	
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
}

void Crafting::onMouseDown()
{
	int xRelativeToList = mouseX - craftingX - listOffsetX;
	int yRelativeToList = mouseY - craftingY - listOffsetY;

	if (xRelativeToList < 0 || xRelativeToList > craftingRecipeWidth
		|| yRelativeToList < 0 || yRelativeToList > craftingListEntriesPerPage*craftingRecipeHeight)
	{
		int xRelativeToCraftingButton = mouseX - craftingX - activeOffsetX - craftingButtonOffsetX;
		int yRelativeToCraftingButton = mouseY - craftingY - activeOffsetY - craftingButtonOffsetY;

		if (activeRecipeIndex != -1)
		{
			if (xRelativeToCraftingButton < 0 || xRelativeToCraftingButton > craftingButtonWidth
				|| yRelativeToCraftingButton < 0 || yRelativeToCraftingButton > craftingButtonHeight)
			{
				return;
			}

			recipes[activeRecipeIndex]->doCraft();
		}

		return;
	}

	activeRecipeIndex = (yRelativeToList/craftingRecipeHeight) + craftingListPage*craftingListEntriesPerPage;
	int x = 123;
}