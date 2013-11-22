#pragma once
#include "fieldback.h"
class FieldBackCoal :
	public FieldBack
{
public:
	FieldBackCoal(void);
	~FieldBackCoal(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();

	void onUsed(const ToolTypes &toolType, const int32_t &toolLevel);
};

