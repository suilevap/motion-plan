#pragma once

template<typename T = int>
struct Point
{
public:
	T X;
	T Y;

	Point(T x, T y)
		:X(x),Y(y)
	{}

	Point()
		:X(0),Y(0)
	{}
};
