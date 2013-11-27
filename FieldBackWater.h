#pragma once
#include "fieldback.h"
class FieldBackWater :
	public FieldBack
{
public:
	FieldBackWater(void);
	~FieldBackWater(void);

	//a counter variable to not do our update stuff on every frame
	float updateCounter;

	int waterLevel;
	int maxWaterLevel;

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);

	void setWaterLevel(int newWaterLevel);
};

