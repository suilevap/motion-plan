#pragma once

#ifndef MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_
#define MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_

#include <math.h>

namespace AStar
{

class DistanceEvaluator
{
public:
	template<typename T>
	inline static T EuclideanDistance(T x1, T y1, T x2, T y2);

	template<typename T>
	inline static T ManhattanDistance(T x1, T y1, T x2, T y2);

	template<typename T>
	inline static T DiagonalDistance(T x1, T y1, T x2, T y2) ;

};

#include "DistanceEvaluator.inl"

}

#endif
