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

	bool operator+ ( const Point<T> &point)
	{
		return Point(X + point.X, Y + point.Y );
	}

	bool operator- ( const Point<T> &point)
	{
		return Point(X - point.X, Y - point.Y );
	}

	bool operator/ ( const T v)
	{
		return Point(X / v, Y / v );
	}

    bool operator* ( const T v)
	{
		return Point(X * v, Y * v );
	}
};
