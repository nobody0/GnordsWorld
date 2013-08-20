#pragma once
#include "Field.h"

class FieldFront : public Field
{
public:
	FieldFront(void);
	virtual ~FieldFront(void);

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1);
	
	void removeFromMap(const int32_t &x, const int32_t &y) const;
	void insertIntoMap(const int32_t &x, const int32_t &y) const;
};