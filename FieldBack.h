#pragma once
#include "Field.h"

class FieldBack : public Field
{
public:
	FieldBack(void);
	virtual ~FieldBack(void);

	virtual void init(const int32_t &x, const int32_t &y, const int32_t &metricsLength = 1, const int32_t &affectedGridsLength = 1);

	virtual void onUsed();
	
	void removeFromMap() const;
	void insertIntoMap() const;
};