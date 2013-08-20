#pragma once
#include "fieldback.h"
class FieldBackGrass :
	public FieldBack
{
public:
	FieldBackGrass(void);
	~FieldBackGrass(void);

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};

