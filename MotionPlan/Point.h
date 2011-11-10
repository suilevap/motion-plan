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

	inline Point<T> operator+ ( const Point<T> &point)
	{
		return Point<T>(X + point.X, Y + point.Y );
	}

	inline Point<T> operator- ( const Point<T> &point)
	{
		return Point<T>(X - point.X, Y - point.Y );
	}

    inline Point<T> operator* ( const Point<T> &point)
	{
		return Point<T>(X * point.X, Y * point.Y );
	}

	inline Point<T> operator/ ( const Point<T> &point)
	{
		return Point<T>(X / point.X, Y / point.Y );
	}

	inline Point<T> operator/ ( const T v)
	{
		return Point<T>(X / v, Y / v );
	}

    inline Point<T> operator* ( const T v)
	{
		return Point<T>(X * v, Y * v );
	}

    inline Point<T> operator+ ( const T v)
	{
		return Point<T>(X + v, Y + v );
	}

    inline Point<T> operator- ( const T v)
	{
		return Point<T>(X - v, Y - v );
	}

    inline bool operator<( const Point<T>& point)
	{
		return (X<point.X && Y<point.Y);
	}

    inline  bool operator>( const Point<T>& point)
	{
		return (X > point.X && Y > point.Y);
	}

    inline  bool operator<( const Point<T>& point) const
	{
		return (X<point.X && Y<point.Y);
	}

    inline bool operator>( const Point<T> &point) const
	{
		return (X > point.X && Y > point.Y);
	}
    inline bool operator==( const Point<T> &point) const
	{
		return (X == point.X && Y == point.Y);
	}

    static Point<T> Avg(const Point<T>& point1, const Point<T>& point2)
    {
        return Point<T>((point1.X +point2.X)/2,(point1.Y + point2.Y)/2 );
    }

    inline T TriArea(const Point<T>& a, const Point<T>& b)
    {
	    const T abx = b.X - a.X;
	    const T abz = b.Y - a.Y;
	    const T acx = X - a.X;
	    const T acz = Y - a.Y;
	    return acx*abz - abx*acz;
    }
};
