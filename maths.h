#pragma once

#include <vector>


namespace fff
{

struct IntPoint
{
	int X, Y;

	IntPoint() : X(0), Y(0)
	{}

	IntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{}

	IntPoint(const IntPoint& Others) : X(Others.X), Y(Others.Y)
	{}

	IntPoint& operator = (const IntPoint& Others)
	{
		if (this != &Others)
		{
			X = Others.X;
			Y = Others.Y;
		}
		return *this;
	}
};

} // namespace fff
