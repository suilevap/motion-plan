#ifndef MOTIONPLAN_DISTANCEEVALUATOR_H_
#error "Include from DistanceEvaluator.h only."
#else

#include "MathConstants.h"

template<typename T>
inline static T DistanceEvaluator::EuclideanDistance(T x1, T y1, T x2, T y2)
{
	return (T) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

template<typename T>
inline static T DistanceEvaluator::ManhattanDistance(T x1, T y1, T x2, T y2) 
{ 
	return (std::abs(x1-x2) + std::abs(y1-y2)); 
}

template<typename T>
inline static T DistanceEvaluator::DiagonalDistance(T x1, T y1, T x2, T y2) 
{ 
	T xd = std::abs(x1-x2);
	T yd = std::abs(y1-y2);
	T diagonal = min(xd, yd);
	T straight = xd + yd;
	return (T)((SQRT_2 * diagonal) + (straight - (2 * diagonal)));
}

#endif
