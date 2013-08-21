#pragma once

using namespace std;

class Vector2
{
public:
	float x;
	float y;

	Vector2(void) : x(0), y(0)
	{

	}
	Vector2(float x, float y) : x(x), y(y)
	{

	}

	~Vector2(void)
	{

	}

	Vector2 operator+(const Vector2 &right)
	{
		Vector2 result;
		result.x = x + right.x;
		result.y = y + right.y;
		return result;
	}

	Vector2& operator+=(const Vector2 &right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}
};

