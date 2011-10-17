#pragma once

#ifndef MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_
#define MOTIONPLAN_ASTAR_DISTANCEEVALUATOR_H_

#include <math.h>
#include "Point.h"


namespace AStar
{

class DistanceEvaluator
{
public:
	template<typename T, typename P>
	inline static T EuclideanDistance(const Point<P>& p1, const Point<P>& p2);

	template<typename T, typename P>
	inline static T ManhattanDistance(const Point<P>& p1, const Point<P>& p2);

	template<typename T, typename P>
	inline static T DiagonalDistance(const Point<P>& p1, const Point<P>& p2) ;

	//for grid like this (where each cell have 4 neighbors in horizontal, and 2 in vertical)
	// 0\ /2\_
	// _/1\_/3\
	// 4\_/6\_/
	// _/5\_/7\
	// 8\_/1\_/
	// _/9\0/11
	template<typename T, typename P>
	inline static T HexShiftByXDistance(const Point<P>& p1, const Point<P>& p2) ;

};

#include "DistanceEvaluator.inl"

}

#endif
