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

    static Point<T> Zero()
    {
        return Point<T>(0, 0);
    }

	Point<T> operator+ ( const Point<T> &point)
	{
		return Point<T>(X + point.X, Y + point.Y );
	}

	Point<T> operator- ( const Point<T> &point)
	{
		return Point<T>(X - point.X, Y - point.Y );
	}

	Point<T> operator/ ( const T v)
	{
		return Point<T>(X / v, Y / v );
	}

    Point<T> operator* ( const T v)
	{
		return Point<T>(X * v, Y * v );
	}

    bool operator<( const Point<T> point)
	{
		return (X<point.X && Y<point.Y);
	}

    bool operator>( const Point<T> point)
	{
		return (X > point.X && Y > point.Y);
	}

    bool operator<( const Point<T> point) const
	{
		return (X<point.X && Y<point.Y);
	}

    bool operator>( const Point<T> point) const
	{
		return (X > point.X && Y > point.Y);
	}

    static Point<T> Avg(const Point<T> point1, const Point<T> point2)
    {
        return Point<T>((point1.X +point2.X)/2,(point1.Y + point2.Y)/2 );
    }
};
