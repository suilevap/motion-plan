#ifndef MOTIONPLAN_DISTANCEEVALUATOR_H_
#error "Include from DistanceEvaluator.h only."
#else

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
	T diagonal = std::min(std::abs(x1-x2), std::abs(y1-y2));
	T straight = std::abs(x1-x2) + std::abs(y1-y2);
	return (T)((sqrt(2.0) * diagonal) + (straight - (2 * diagonal)));
}

#endif
