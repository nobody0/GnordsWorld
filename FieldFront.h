#pragma once
#include "Field.h"

class FieldFront : public Field
{
public:
	FieldFront(void);
	virtual ~FieldFront(void);

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1, const int32_t &affectedGridsLength = 1);
	
	void removeFromMap() const;
	void insertIntoMap() const;
};