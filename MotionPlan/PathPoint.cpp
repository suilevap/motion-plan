#include "StdAfx.h"
#include "PathPoint.h"

PathPoint::PathPoint(void)
{
}

PathPoint::~PathPoint(void)
{
}

//Overload the < operator.
bool PathPoint::operator< ( const PathPoint &point2)
{
	return Rank < point2.Rank;	
}
//Overload the > operator.
bool PathPoint::operator> ( const PathPoint &point2)
{
	return Rank > point2.Rank;	
}

//Overload the < operator.
bool operator< (const PathPoint &point1, const PathPoint &point2)
{
	return point1.Rank < point2.Rank;	
}
//Overload the > operator.
bool operator> (const PathPoint &point1, const PathPoint &point2)
{
	return point1.Rank > point2.Rank;	
}
	