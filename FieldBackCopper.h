#pragma once
#include "fieldback.h"
class FieldBackCopper :
	public FieldBack
{
public:
	FieldBackCopper(void);
	~FieldBackCopper(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};

