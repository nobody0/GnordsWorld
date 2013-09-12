#include "Fists.h"


Fists::Fists(void)
{
}


Fists::~Fists(void)
{
}

void Fists::onUse(Field* target, const int32_t &x, const int32_t &y)
{
	if (target != NULL)
	{
		target->onUsed();
	}
}