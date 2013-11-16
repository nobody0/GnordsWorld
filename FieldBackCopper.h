#pragma once
#include "fieldback.h"
class FieldBackCopper :
	public FieldBack
{
public:
	FieldBackCopper(void);
	~FieldBackCopper(void);

	float updateCounter;

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);
};

