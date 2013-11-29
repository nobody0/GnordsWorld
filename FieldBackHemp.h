#pragma once
#include "fieldback.h"
class FieldBackHemp :
	public FieldBack
{
public:
	FieldBackHemp(void);
	~FieldBackHemp(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);
};

