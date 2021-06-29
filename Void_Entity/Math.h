#ifndef MATH_H_
#define MATH_H_

enum Direction
{
	DIR_LEFT = -1,
	DIR_RIGHT = 1,
};

struct Vec2
{
	float x, y;

	Vec2()
		: x(0.0f)
		, y(0.0f)
	{ }

	Vec2(float x, float y)
		: x(x)
		, y(y)
	{ }
};

#endif
