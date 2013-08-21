#include "Rect.h"
#include "Math.h"


Rect::Rect(void) : x(0), y(0), w(0), h(0)
{
}


Rect::~Rect(void)
{
}

bool Rect::collidesWith(const Rect &rect2)
{
	if (   (x + w < rect2.x)
		|| (y + h < rect2.y)
		|| (rect2.x + rect2.w < x)
		|| (rect2.y + rect2.h < y) )
	{
		return false;
	}

	return true;
}

bool Rect::intersectsWith(const Rect &rect2)
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

bool Rect::shortenVectorToNotInteresctWith(const Rect &rect2, Vector2 &moveVector)
{
	if (moveVector.x > 0)
	{
		float xCeiled = ceil(moveVector.x);
		float temp = x + w - rect2.x;
		if (temp < xCeiled && temp != 0)
		{
			moveVector.x -= temp;
			return true;
		}
		if (temp == xCeiled)
		{
			moveVector.x = 0;
			return true;
		}
	}

	if (moveVector.x < 0)
	{
		float xFloored = floor(moveVector.x);
		float temp = x - (rect2.x + rect2.w);
		if (temp > xFloored && temp != 0)
		{
			moveVector.x -= temp;
			return true;
		}
		if (temp == xFloored)
		{
			moveVector.x = 0;
			return true;
		}
	}

	if (moveVector.y > 0)
	{
		float yCeiled = ceil(moveVector.y);
		float temp = y + h - rect2.y;
		if (temp < yCeiled && temp != 0)
		{
			moveVector.y -= temp;
			return true;
		}
		if (temp == yCeiled)
		{
			moveVector.y = 0;
			return true;
		}
	}

	if (moveVector.y < 0)
	{
		float yFloored = floor(moveVector.y);
		float temp = y - (rect2.y + rect2.h);
		if (temp > yFloored && temp != 0)
		{
			moveVector.y -= temp;
			return true;
		}
		if (temp == yFloored)
		{
			moveVector.y = 0;
			return true;
		}
	}

	moveVector.x = 0;
	moveVector.y = 0;
	return false;
}