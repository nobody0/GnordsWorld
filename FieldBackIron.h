#pragma once
#include "fieldback.h"
class FieldBackIron :
	public FieldBack
{
public:
	FieldBackIron(void);
	~FieldBackIron(void);

	float updateCounter;

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);
};

