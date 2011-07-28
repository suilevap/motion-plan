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
	inline static T EuclideanDistance(const Point& p1, const Point& p2);

	template<typename T>
	inline static T ManhattanDistance(const Point& p1, const Point& p2);

	template<typename T>
	inline static T DiagonalDistance(const Point& p1, const Point& p2) ;

};

#include "DistanceEvaluator.inl"

}

#endif
