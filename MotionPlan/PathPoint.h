#pragma once

struct PathPoint
{
public:
	int Index;
	float Rank;

		//Overload the < operator.
	bool operator< ( const PathPoint &point2)
	{
		return Rank < point2.Rank;	
	}
	//Overload the > operator.
	bool operator> ( const PathPoint &point2)
	{
		return Rank > point2.Rank;	
	}
};

//Overload the < operator.
bool operator< (const PathPoint& point1, const PathPoint &point2)
{
	return point1.Rank < point2.Rank;	
}
//Overload the > operator.
bool operator> (const PathPoint& point1, const PathPoint &point2)
{
	return point1.Rank > point2.Rank;	
}
	