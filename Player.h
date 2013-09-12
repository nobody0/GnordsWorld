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
	
	void init(const int32_t &x, const int32_t &y);

	void updateMetrics(Rect* const &metrics, const int32_t &x, const int32_t &y);

	void myUpdate();

	void useTool(Field* target, const int32_t &x, const int32_t &y);
};