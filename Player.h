#pragma once
#include "FieldFront.h"
#include "CreatureStates.h"

class Player : public FieldFront
{
public:
	Player(void);
	virtual ~Player(void);

	CreatureStates state;
	
	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};