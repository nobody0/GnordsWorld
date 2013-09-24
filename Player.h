#pragma once
#include "FieldFront.h"
#include "Inventory.h"
#include "Fists.h"

class Player : public FieldFront
{
public:
	Inventory inventory;
	InventoryObject* activeTool;
	Fists defaultTool;

	Player(void);
	virtual ~Player(void);

	void draw(bool forceRedraw = false);
	
	void init(const int32_t &x, const int32_t &y);

	void updateMetrics(Rect* const &metrics, int64_t* const &affectedGrids, const int32_t &x, const int32_t &y);

	void myUpdate();

	void useTool(Field* target, const int32_t &x, const int32_t &y);

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);

private:
	SDL_Surface* body[6];
	SDL_Surface* bodyFlipped[6];
	SDL_Surface* fell;
	SDL_Surface* fellFlipped;
	SDL_Surface* arm[8];
	SDL_Surface* armFlipped[8];
	
	float bodyAnimStart;
	uint32_t bodyAnimIndex;
	
	float armAnimStart;
	uint32_t armAnimIndex;

	bool flip;
};