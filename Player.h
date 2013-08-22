#pragma once
#include "FieldFront.h"

class Player : public FieldFront
{
public:
	Player(void);
	virtual ~Player(void);
	
	void init(const int32_t &x, const int32_t &y);

	void updateMetrics(Rect* const &metrics, const int32_t &x, const int32_t &y);

	void myUpdate();
};