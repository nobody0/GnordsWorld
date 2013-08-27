#pragma once
#include "fieldback.h"
class FieldBackStone :
	public FieldBack
{
public:
	FieldBackStone(void);
	~FieldBackStone(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};

