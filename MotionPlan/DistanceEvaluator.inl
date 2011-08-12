#ifndef MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_
#error "Include from DistanceEvaluator.h only."
#else

#include "MathConstants.h"

template<typename T, typename P>
inline static T DistanceEvaluator::EuclideanDistance(const Point<P>& p1, const Point<P>& p2)
{
	return (T) sqrt((T)((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y)));
}

template<typename T, typename P >
inline static T DistanceEvaluator::ManhattanDistance(const Point<P>& p1, const Point<P>& p2) 
{ 
	return (T)(std::abs(p1.X - p2.X) + std::abs(p1.Y - p2.Y)); 
}

template<typename T, typename P>
inline static T DistanceEvaluator::DiagonalDistance(const Point<P>& p1, const Point<P>& p2) 
{ 
	P xd = std::abs(p1.X - p2.X);
	P yd = std::abs(p1.Y - p2.Y);
	T diagonal = min(xd, yd);
	T straight = xd + yd;
	return (T)((SQRT_2 * diagonal) + (straight - (2 * diagonal)));
}

template<typename T, typename P>
inline static T DistanceEvaluator::HexShiftByXDistance(const Point<P>& p1, const Point<P>& p2) 
{

	P xd = std::abs(p1.X - p2.X)* 2;
	P yd = std::abs((p1.Y - p2.Y)*2+(p1.X%2-p2.X%2));

	T result;

	if (xd >= yd * 2)// x more than  needed for diagonal	
	{
		result = static_cast<T>(xd/2);
	}
	else //need some vertical movements
	{
		result = static_cast<T>((xd/2 + yd)/2);
	}
	return result;
}

#endif
