#pragma once
#include "fieldback.h"
class FieldBackEarth :
	public FieldBack
{
public:
	FieldBackEarth(void);
	virtual ~FieldBackEarth(void);

	//a counter variable to not do our update stuff on every frame
	uint32_t updateCounter;

	void init(const int32_t &x, const int32_t &y);

	void myUpdate();
};

