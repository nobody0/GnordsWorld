#pragma once
#include "fieldback.h"
class FieldBackIron :
	public FieldBack
{
public:
	FieldBackIron(void);
	~FieldBackIron(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};

