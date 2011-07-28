#ifndef MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_
#error "Include from DistanceEvaluator.h only."
#else

#include "MathConstants.h"

template<typename T>
inline static T DistanceEvaluator::EuclideanDistance(const Point& p1, const Point& p2)
{
	return (T) sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
}

template<typename T>
inline static T DistanceEvaluator::ManhattanDistance(const Point& p1, const Point& p2) 
{ 
	return (std::abs(p1.X - p2.X) + std::abs(p1.Y - p2.Y)); 
}

template<typename T>
inline static T DistanceEvaluator::DiagonalDistance(const Point& p1, const Point& p2) 
{ 
	T xd = std::abs(p1.X - p2.X);
	T yd = std::abs(p1.Y - p2.Y);
	T diagonal = min(xd, yd);
	T straight = xd + yd;
	return (T)((SQRT_2 * diagonal) + (straight - (2 * diagonal)));
}

#endif
