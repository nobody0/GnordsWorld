#pragma once
#include "Field.h"

class FieldBack : public Field
{
public:
	FieldBack(void);
	virtual ~FieldBack(void);

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1);
	
	void removeFromMap(const int32_t &x, const int32_t &y) const;
	void insertIntoMap(const int32_t &x, const int32_t &y) const;
};