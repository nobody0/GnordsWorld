#include "Rect.h"


Rect::Rect(void)
{
}


Rect::~Rect(void)
{
}

bool Rect::collidesWith(const Rect &rect2)
{
	if (   (x + w <= rect2.x)
		|| (y + h <= rect2.y)
		|| (rect2.x + rect2.w <= x)
		|| (rect2.y + rect2.h <= y) )
	{
		return false;
	}

	return true;
}